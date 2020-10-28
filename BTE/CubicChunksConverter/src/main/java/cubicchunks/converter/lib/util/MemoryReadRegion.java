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

import static java.nio.file.StandardOpenOption.CREATE;
import static java.nio.file.StandardOpenOption.READ;
import static java.nio.file.StandardOpenOption.WRITE;

import cubicchunks.regionlib.api.region.IRegion;
import cubicchunks.regionlib.api.region.IRegionProvider;
import cubicchunks.regionlib.api.region.key.IKey;
import cubicchunks.regionlib.api.region.key.IKeyProvider;
import cubicchunks.regionlib.api.region.key.RegionKey;
import cubicchunks.regionlib.lib.Region;
import cubicchunks.regionlib.lib.header.IKeyIdToSectorMap;
import cubicchunks.regionlib.lib.header.IntPackedSectorMap;
import cubicchunks.regionlib.util.CheckedConsumer;
import cubicchunks.regionlib.util.CorruptedDataException;
import cubicchunks.regionlib.util.WrappedException;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MemoryReadRegion<K extends IKey<K>> implements IRegion<K> {

    private final IKeyIdToSectorMap<?, ?, K> sectorMap;
    private final int sectorSize;
    private SeekableByteChannel file;
    private final RegionKey regionKey;
    private final IKeyProvider<K> keyProvider;
    private final int keyCount;
    private ByteBuffer fileBuffer;

    private MemoryReadRegion(SeekableByteChannel file,
            IntPackedSectorMap<K> sectorMap,
            RegionKey regionKey,
            IKeyProvider<K> keyProvider,
            int sectorSize) throws IOException {
        this.file = file;
        this.regionKey = regionKey;
        this.keyProvider = keyProvider;
        this.keyCount = keyProvider.getKeyCount(regionKey);
        this.sectorSize = sectorSize;
        this.sectorMap = sectorMap;
    }

    @Override public synchronized void writeValue(K key, ByteBuffer value) throws IOException {
        throw new UnsupportedOperationException("Writing not supported in this implementation");
    }

    @Override public void writeSpecial(K key, Object marker) throws IOException {
        throw new UnsupportedOperationException("Writing not supported in this implementation");
    }

    @Override public synchronized Optional<ByteBuffer> readValue(K key) throws IOException {
        if (fileBuffer == null) {
            this.fileBuffer = ByteBuffer.allocate((int) file.size());

            file.position(0);
            file.read(fileBuffer);
            file.close();
            file = null;
        }
        // a hack because Optional can't throw checked exceptions
        try {
            return sectorMap.trySpecialValue(key)
                    .map(reader -> Optional.of(reader.apply(key)))
                    .orElseGet(() -> doReadKey(key));
        } catch (WrappedException e) {
            throw (IOException) e.get();
        }
    }

    private Optional<ByteBuffer> doReadKey(K key) {
        return sectorMap.getEntryLocation(key).flatMap(loc -> {
            try {
                int sectorOffset = loc.getOffset();
                int sectorCount = loc.getSize();

                fileBuffer.limit(sectorOffset * sectorSize + Integer.BYTES);
                fileBuffer.position(sectorOffset * sectorSize);
                int dataLength = fileBuffer.getInt();
                if (dataLength > sectorCount * sectorSize) {
                    throw new CorruptedDataException(
                            "Expected data size max" + sectorCount * sectorSize + " but found " + dataLength);
                }
                fileBuffer.position(sectorOffset * sectorSize + Integer.BYTES);
                fileBuffer.limit(sectorOffset * sectorSize + Integer.BYTES + dataLength);

                return Optional.of(ByteBuffer.allocate(dataLength).put(fileBuffer));
            } catch (IOException e) {
                throw new WrappedException(e);
            }
        });
    }

    /**
     * Returns true if something was stored there before within this region.
     */
    @Override public synchronized boolean hasValue(K key) {
        return sectorMap.getEntryLocation(key).isPresent();
    }

    @Override public void forEachKey(CheckedConsumer<? super K, IOException> cons) throws IOException {
        for (int id = 0; id < this.keyCount; id++) {
            int idFinal = id; // because java is stupid
            K key = sectorMap.getEntryLocation(id).map(loc -> keyProvider.fromRegionAndId(this.regionKey, idFinal)).orElse(null);
            if (key != null) {
                cons.accept(key);
            }
        }
    }


    private int getSectorNumber(int bytes) {
        return ceilDiv(bytes, sectorSize);
    }

    @Override public void close() throws IOException {
        if (file != null) {
            file.close();
        }
    }

    private static int ceilDiv(int x, int y) {
        return -Math.floorDiv(-x, y);
    }

    public static <L extends IKey<L>> Region.Builder<L> builder() {
        return new Region.Builder<>();
    }

    /**
     * Internal Region builder. Using it is very unsafe, there are no safeguards against using it improperly. Should only be used by
     * {@link IRegionProvider} implementations.
     */
    // TODO: make a safer to use builder
    public static class Builder<K extends IKey<K>> {

        private Path directory;
        private int sectorSize = 512;
        private RegionKey regionKey;
        private IKeyProvider<K> keyProvider;
        private List<IntPackedSectorMap.SpecialSectorMapEntry<K>> specialEntries = new ArrayList<>();

        public MemoryReadRegion.Builder<K> setDirectory(Path path) {
            this.directory = path;
            return this;
        }

        public MemoryReadRegion.Builder<K> setRegionKey(RegionKey key) {
            this.regionKey = key;
            return this;
        }

        public MemoryReadRegion.Builder<K> setKeyProvider(IKeyProvider<K> keyProvider) {
            this.keyProvider = keyProvider;
            return this;
        }

        public MemoryReadRegion.Builder<K> setSectorSize(int sectorSize) {
            this.sectorSize = sectorSize;
            return this;
        }

        public MemoryReadRegion<K> build() throws IOException {
            SeekableByteChannel file = Files.newByteChannel(directory.resolve(regionKey.getName()), CREATE, READ, WRITE);
            IntPackedSectorMap<K> sectorMap = IntPackedSectorMap.readOrCreate(file, keyProvider.getKeyCount(regionKey), specialEntries);
            return new MemoryReadRegion<>(file, sectorMap, this.regionKey, keyProvider, this.sectorSize);
        }
    }
}
