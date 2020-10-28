/*
 *  This file is part of CubicChunksConverter, licensed under the MIT License (MIT).
 *
 *  Copyright (c) 2017 contributors
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
package cubicchunks.converter.lib.util;

import cubicchunks.regionlib.api.region.IRegion;
import cubicchunks.regionlib.api.region.IRegionProvider;
import cubicchunks.regionlib.api.region.key.IKey;
import cubicchunks.regionlib.api.region.key.RegionKey;
import cubicchunks.regionlib.util.CheckedBiConsumer;
import cubicchunks.regionlib.util.CheckedConsumer;
import cubicchunks.regionlib.util.CheckedFunction;

import java.io.IOException;
import java.util.Iterator;
import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * A region caching provider that uses a shared underlying cache for all instances
 */
public class RWLockingCachedRegionProvider<K extends IKey<K>> implements IRegionProvider<K> {

    private final IRegionProvider<K> sourceProvider;

    private final ReadWriteLock lock = new ReentrantReadWriteLock();
    private final Map<RegionKey, IRegion<?>> regionLocationToRegion = new ConcurrentHashMap<>(512);
    private final int maxCacheSize = 64;

    private boolean closed;

    /**
     * Creates a RegionProvider using the given {@code regionFactory} and {@code maxCacheSize}
     *
     * @param sourceProvider provider used as source of regions
     */
    public RWLockingCachedRegionProvider(IRegionProvider<K> sourceProvider) {
        this.sourceProvider = sourceProvider;
    }

    @Override
    public <R> Optional<R> fromExistingRegion(K key, CheckedFunction<? super IRegion<K>, R, IOException> func) throws IOException {
        if (closed) {
            throw new IllegalStateException("Already closed");
        }
        return fromRegion(key, func, false);
    }

    @Override
    public <R> R fromRegion(K key, CheckedFunction<? super IRegion<K>, R, IOException> func) throws IOException {
        if (closed) {
            throw new IllegalStateException("Already closed");
        }
        return fromRegion(key, func, true).get();
    }

    @Override
    public void forRegion(K key, CheckedConsumer<? super IRegion<K>, IOException> cons) throws IOException {
        if (closed) {
            throw new IllegalStateException("Already closed");
        }
        forRegion(key, cons, true);
    }

    @Override
    public void forExistingRegion(K key, CheckedConsumer<? super IRegion<K>, IOException> cons) throws IOException {
        if (closed) {
            throw new IllegalStateException("Already closed");
        }
        forRegion(key, cons, false);
    }

    @SuppressWarnings("unchecked") @Override public IRegion<K> getRegion(K key) throws IOException {
        Lock writeLock = lock.writeLock();
        RegionKey regionKey = key.getRegionKey();
        writeLock.lock();
        try {
            IRegion<K> r = (IRegion<K>) regionLocationToRegion.get(regionKey);
            if (r != null) {
                regionLocationToRegion.remove(regionKey);
                return r;
            } else {
                return sourceProvider.getRegion(key);
            }
        } finally {
            writeLock.unlock();
        }
    }

    @SuppressWarnings("unchecked") @Override public Optional<IRegion<K>> getExistingRegion(K key) throws IOException {
        Lock writeLock = lock.writeLock();
        RegionKey regionKey = key.getRegionKey();
        writeLock.lock();
        try {
            IRegion<K> r = (IRegion<K>) regionLocationToRegion.get(regionKey);
            if (r != null) {
                regionLocationToRegion.remove(regionKey);
                return Optional.of(r);
            } else {
                return sourceProvider.getExistingRegion(key);
            }
        } finally {
            writeLock.unlock();
        }
    }

    @Override public void forAllRegions(CheckedBiConsumer<RegionKey, ? super IRegion<K>, IOException> consumer) throws IOException {
        if (closed) {
            throw new IllegalStateException("Already closed");
        }
        sourceProvider.forAllRegions(consumer);
    }

    @Override public void close() throws IOException {
        synchronized (regionLocationToRegion) {
            if (closed) {
                throw new IllegalStateException("Already closed");
            }
            clearRegions();
            this.sourceProvider.close();
            this.closed = true;
        }
    }

    @SuppressWarnings("unchecked")
    private void forRegion(K location, CheckedConsumer<? super IRegion<K>, IOException> cons, boolean canCreate) throws IOException {
        if (regionLocationToRegion.size() > maxCacheSize) {
            clearRegions();
        }
        IRegion<K> region;
        Lock readLock = lock.readLock();
        Lock writeLock = lock.writeLock();
        boolean createNew = false;

        RegionKey regionKey = location.getRegionKey();

        readLock.lock();
        try {
            region = (IRegion<K>) regionLocationToRegion.get(regionKey);
            if (region == null) {
                region = sourceProvider.getExistingRegion(location).orElse(null);
                if (region != null) {
                    regionLocationToRegion.put(regionKey, region);
                }
                if (region == null && canCreate) {
                    createNew = true;
                }
            }

            if (region != null) {
                cons.accept(region);
            }
        } finally {
            readLock.unlock();
        }
        if (createNew) {
            writeLock.lock();
            try {
                region = sourceProvider.getRegion(location);
                regionLocationToRegion.put(regionKey, region);
                cons.accept(region);
            } finally {
                writeLock.unlock();
            }
        }
    }

    @SuppressWarnings("unchecked")
    public <R> Optional<R> fromRegion(K location, CheckedFunction<? super IRegion<K>, R, IOException> func, boolean canCreate) throws IOException {
        if (regionLocationToRegion.size() > maxCacheSize) {
            clearRegions();
        }
        IRegion<K> region;
        Lock readLock = lock.readLock();
        Lock writeLock = lock.writeLock();
        boolean createNew = false;

        RegionKey regionKey = location.getRegionKey();

        readLock.lock();
        try {
            region = (IRegion<K>) regionLocationToRegion.get(regionKey);
            if (region == null) {
                region = sourceProvider.getExistingRegion(location).orElse(null);
                if (region != null) {
                    regionLocationToRegion.put(regionKey, region);
                }
                if (region == null && canCreate) {
                    createNew = true;
                }
            }

            if (region != null) {
                return Optional.of(func.apply(region));
            }
        } finally {
            readLock.unlock();
        }
        if (createNew) {
            writeLock.lock();
            try {
                region = sourceProvider.getRegion(location);
                regionLocationToRegion.put(regionKey, region);
                return Optional.of(func.apply(region));
            } finally {
                writeLock.unlock();
            }
        }
        return Optional.empty();
    }

    public synchronized void clearRegions() throws IOException {
        lock.writeLock().lock();
        try {
            Iterator<IRegion<?>> it = regionLocationToRegion.values().iterator();
            while (it.hasNext()) {
                it.next().close();
            }
            regionLocationToRegion.clear();
        } finally {
            lock.writeLock().unlock();
        }
    }
}
