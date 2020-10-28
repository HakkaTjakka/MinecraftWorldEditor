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
package cubicchunks.converter.lib.convert.io;


import static cubicchunks.converter.lib.util.Utils.propagateExceptions;
import static cubicchunks.regionlib.impl.save.MinecraftSaveSection.MinecraftRegionType.MCA;

import cubicchunks.converter.lib.Dimension;
import cubicchunks.converter.lib.convert.ChunkDataWriter;
import cubicchunks.converter.lib.convert.data.AnvilChunkData;
import cubicchunks.converter.lib.convert.data.MultilayerAnvilChunkData;
import cubicchunks.converter.lib.util.MemoryWriteRegion;
import cubicchunks.converter.lib.util.RWLockingCachedRegionProvider;
import cubicchunks.converter.lib.util.Utils;
import cubicchunks.regionlib.impl.MinecraftChunkLocation;
import cubicchunks.regionlib.impl.header.TimestampHeaderEntryProvider;
import cubicchunks.regionlib.impl.save.MinecraftSaveSection;
import cubicchunks.regionlib.lib.Region;
import cubicchunks.regionlib.lib.provider.SimpleRegionProvider;

import java.io.Closeable;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;

public class AnvilChunkWriter implements ChunkDataWriter<MultilayerAnvilChunkData> {

    private Path dstPath;
    private Map<Integer, Map<Dimension, MinecraftSaveSection>> saves = new ConcurrentHashMap<>();

    public AnvilChunkWriter(Path dstPath) {
        this.dstPath = dstPath;
    }

    @Override public void accept(MultilayerAnvilChunkData data) throws IOException {
        for (Map.Entry<Integer, AnvilChunkData> entry : data.getWorlds().entrySet()) {
            int layerY = entry.getKey();
            AnvilChunkData chunk = entry.getValue();
            Map<Dimension, MinecraftSaveSection> layer = saves.computeIfAbsent(layerY, i -> new HashMap<>());
            MinecraftSaveSection save = layer.computeIfAbsent(chunk.getDimension(), propagateExceptions(dim -> {
                Path regionDir = getDimensionPath(entry.getValue().getDimension(), dstPath.resolve(dirName(layerY)));
                Utils.createDirectories(regionDir);
                return new MinecraftSaveSection(new RWLockingCachedRegionProvider<>(
                        new SimpleRegionProvider<>(new MinecraftChunkLocation.Provider(MCA.name().toLowerCase()), regionDir, (keyProvider, regionKey) ->
                                MemoryWriteRegion.<MinecraftChunkLocation>builder()
                                        .setDirectory(regionDir)
                                        .setSectorSize(4096)
                                        .setKeyProvider(keyProvider)
                                        .setRegionKey(regionKey)
                                        .addHeaderEntry(new TimestampHeaderEntryProvider<>(TimeUnit.MILLISECONDS))
                                        .build(),
                                (file, key) -> Files.exists(file)
                        )
                ));
            }));
            save.save(chunk.getPosition(), chunk.getData());
        }
    }

    static Path getDimensionPath(Dimension d, Path worldDir) {
        if (!d.getDirectory().isEmpty()) {
            worldDir = worldDir.resolve(d.getDirectory());
        }
        return worldDir.resolve("region");
    }


    static String dirName(int layerY) {
        return String.format("layer [%d, %d)", layerY * 256, (layerY + 1) * 256);
    }

    @Override public void discardData() throws IOException {
        Utils.rm(dstPath);
    }

    @Override public void close() throws Exception {
        boolean exception = false;
        for (Map<?, ? extends Closeable> saves : this.saves.values()) {
            for (Closeable save : saves.values()) {
                try {
                    save.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    exception = true;
                }
            }
        }

        if (exception) {
            throw new IOException();
        }
    }
}
