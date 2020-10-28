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
import cubicchunks.regionlib.api.region.key.IKey;
import cubicchunks.regionlib.api.region.key.IKeyProvider;
import cubicchunks.regionlib.api.region.key.RegionKey;
import cubicchunks.regionlib.util.CheckedConsumer;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Optional;

import static java.nio.file.StandardOpenOption.*;

public class FragmentedMemoryWriteRegion<K extends IKey<K>> implements IRegion<K> {

    private static final int SIZE_BITS = 8;
    private static final int OFFSET_BITS = Integer.SIZE - SIZE_BITS;
    private static final int SIZE_MASK = (1 << SIZE_BITS) - 1;
    private static final int MAX_SIZE = SIZE_MASK;
    private static final int OFFSET_MASK = (1 << OFFSET_BITS) - 1;
    private static final int MAX_OFFSET = OFFSET_MASK;

    private final SeekableByteChannel file;
    private final int sectorSize;
    private final int keyCount;
    private ByteBuffer[] writeEntries;

    private FragmentedMemoryWriteRegion(SeekableByteChannel file,
                              RegionKey regionKey,
                              IKeyProvider<K> keyProvider,
                              int sectorSize) throws IOException {
        this.keyCount = keyProvider.getKeyCount(regionKey);
        this.file = file;
        this.sectorSize = sectorSize;
    }

    @Override
    public void writeValue(K key, ByteBuffer value) throws IOException {

    }

    @Override
    public void writeSpecial(K key, Object marker) throws IOException {
        throw new UnsupportedOperationException("writeSpecial not supported");
    }

    @Override
    public Optional<ByteBuffer> readValue(K key) throws IOException {
        throw new UnsupportedOperationException("readValue not supported");
    }

    @Override
    public boolean hasValue(K key) {
        throw new UnsupportedOperationException("hasValue not supported");
    }

    @Override
    public void forEachKey(CheckedConsumer<? super K, IOException> cons) throws IOException {
        throw new UnsupportedOperationException("forEachKey not supported");
    }

    @Override
    public void close() throws IOException {

    }

    public static class Builder<K extends IKey<K>> {

        private Path directory;
        private int sectorSize = 512;
        private RegionKey regionKey;
        private IKeyProvider<K> keyProvider;

        public FragmentedMemoryWriteRegion.Builder<K> setDirectory(Path path) {
            this.directory = path;
            return this;
        }

        public FragmentedMemoryWriteRegion.Builder<K> setRegionKey(RegionKey key) {
            this.regionKey = key;
            return this;
        }

        public FragmentedMemoryWriteRegion.Builder<K> setKeyProvider(IKeyProvider<K> keyProvider) {
            this.keyProvider = keyProvider;
            return this;
        }

        public FragmentedMemoryWriteRegion.Builder<K> setSectorSize(int sectorSize) {
            this.sectorSize = sectorSize;
            return this;
        }

        public FragmentedMemoryWriteRegion<K> build() throws IOException {
            SeekableByteChannel file = Files.newByteChannel(directory.resolve(regionKey.getName()), CREATE, READ, WRITE);
            return new FragmentedMemoryWriteRegion<>(file, this.regionKey, keyProvider, this.sectorSize);
        }
    }
}
