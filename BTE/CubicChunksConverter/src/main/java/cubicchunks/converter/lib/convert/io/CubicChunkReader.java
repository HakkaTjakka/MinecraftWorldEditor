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

import static cubicchunks.converter.lib.util.Utils.interruptibleConsumer;

import com.carrotsearch.hppc.IntArrayList;
import com.carrotsearch.hppc.cursors.IntCursor;
import cubicchunks.converter.lib.Dimension;
import cubicchunks.converter.lib.conf.ConverterConfig;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.util.*;
import cubicchunks.regionlib.api.region.IRegionProvider;
import cubicchunks.regionlib.api.region.key.RegionKey;
import cubicchunks.regionlib.impl.EntryLocation2D;
import cubicchunks.regionlib.impl.EntryLocation3D;
import cubicchunks.regionlib.impl.SaveCubeColumns;
import cubicchunks.regionlib.impl.save.SaveSection2D;
import cubicchunks.regionlib.impl.save.SaveSection3D;
import cubicchunks.regionlib.lib.ExtRegion;
import cubicchunks.regionlib.lib.provider.SimpleRegionProvider;
import cubicchunks.regionlib.util.CheckedConsumer;

import java.io.IOException;
import java.io.UncheckedIOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.AbstractMap;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.WeakHashMap;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutionException;
import java.util.function.Consumer;

public class CubicChunkReader extends BaseMinecraftReader<CubicChunksColumnData, SaveCubeColumns> {

    private final CompletableFuture<ChunkList> chunkList = new CompletableFuture<>();
    private final Thread loadThread;
    private static final Map<SaveCubeColumns, List<IRegionProvider<EntryLocation2D>>> providers2d = new WeakHashMap<>();
    private static final Map<SaveCubeColumns, List<IRegionProvider<EntryLocation3D>>> providers3d = new WeakHashMap<>();

    private final List<BoundingBox> regionBoundingBoxes;

    public CubicChunkReader(Path srcDir, ConverterConfig config) {
        super(srcDir, (dim, path) -> Files.exists(getDimensionPath(dim, path)) ? createSave(getDimensionPath(dim, path)) : null);
        loadThread = Thread.currentThread();
        if(config.hasValue("relocations")) {
            this.regionBoundingBoxes = new ArrayList<>();
            @SuppressWarnings("unchecked") List<EditTask> tasks = (List<EditTask>) config.getValue("relocations");
            for (EditTask task : tasks) {
                regionBoundingBoxes.add(task.getSourceBox().asRegionCoords(new Vector3i(16, 16, 16)));
                if (task.getOffset() != null) {
                    regionBoundingBoxes.add(task.getSourceBox().add(task.getOffset()).asRegionCoords(new Vector3i(16, 16, 16)));
                }
            }
        } else
            regionBoundingBoxes = null;
    }

    private static Path getDimensionPath(Dimension d, Path worldDir) {
        if (!d.getDirectory().isEmpty()) {
            worldDir = worldDir.resolve(d.getDirectory());
        }
        return worldDir;
    }

    @Override public void countInputChunks(Runnable increment) throws IOException {
        try {
            Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> dimensions = doCountChunks(increment);
            chunkList.complete(new ChunkList(dimensions));
        } catch (UncheckedInterruptedException ex) {
            chunkList.complete(null);
        }
    }

    private Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> doCountChunks(Runnable increment) throws IOException, UncheckedInterruptedException {
        Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> dimensions = new HashMap<>();
        for (Map.Entry<Dimension, SaveCubeColumns> entry : saves.entrySet()) {
            SaveCubeColumns save = entry.getValue();
            Dimension dim = entry.getKey();
            List<Map.Entry<EntryLocation2D, IntArrayList>> chunks = dimensions.computeIfAbsent(dim, p -> new ArrayList<>());
            Map<EntryLocation2D, IntArrayList> chunksMap = new ConcurrentHashMap<>();

            List<IRegionProvider<EntryLocation3D>> regionProviders = providers3d.get(save);

            CheckedConsumer<EntryLocation3D, IOException> cons = interruptibleConsumer(loc -> {
                EntryLocation2D loc2d = new EntryLocation2D(loc.getEntryX(), loc.getEntryZ());
                chunksMap.computeIfAbsent(loc2d, l -> {
                    increment.run();
                    IntArrayList arr = new IntArrayList();
                    chunks.add(new AbstractMap.SimpleEntry<>(loc2d, arr));
                    return arr;
                }).add(loc.getEntryY());
            });

            for (int i = 0; i < regionProviders.size(); i++) {
                IRegionProvider<EntryLocation3D> p = regionProviders.get(i);
                if (i == 0) {

                    p.forAllRegions((key, reg) -> {
                        Vector3i regionPos = toRegionPos(key);
                        boolean filtered = true;
                        try {
                            if(regionBoundingBoxes != null) {
                                for (BoundingBox regionBox: regionBoundingBoxes) {
                                    if (regionBox.intersects(regionPos.getX(), regionPos.getY(), regionPos.getZ())) {
                                        filtered = false;
                                    }
                                }
                            } else {
                                filtered = false;
                            }
                            if(!filtered) {
                                reg.forEachKey(cons);
                                reg.close();
                            }
                        } catch (IOException e) {
                            throw new UncheckedIOException(e);
                        }
                    });
                } else {
                    int max = i;
                    p.forAllRegions((regionKey, reg) -> {
                        Vector3i regionPos = toRegionPos(regionKey);
                        boolean filtered = true;

                        if(regionBoundingBoxes != null) {
                            for (BoundingBox regionBox: regionBoundingBoxes) {
                                if (regionBox.intersects(regionPos.getX(), regionPos.getY(), regionPos.getZ())) {
                                    filtered = false;
                                }
                            }
                        } else {
                            filtered = false;
                        }
                        if(filtered) {
                            return;
                        }

                        reg.forEachKey(key -> {
                            // cancel if any of the providers before contain this key
                            for (int j = 0; j < max; j++) {
                                EntryLocation3D superKey = regionProviders.get(j)
                                        .getExistingRegion(key)
                                        .flatMap(r -> r.hasValue(key) ? Optional.of(key) : Optional.empty())
                                        .orElse(null);
                                if (superKey != null) {
                                    return;
                                }
                            }
                            cons.accept(key);
                        });
                        reg.close();
                    });
                }
            }
        }
        return dimensions;
    }

    @Override public void loadChunks(Consumer<? super CubicChunksColumnData> consumer) throws IOException, InterruptedException {
        try {
            ChunkList list = chunkList.get();
            if (list == null) {
                return; // counting interrupted
            }
            doLoadChunks(consumer, list);
        } catch (ExecutionException e) {
            throw new RuntimeException(e);
        }
    }

    private void doLoadChunks(Consumer<? super CubicChunksColumnData> consumer, ChunkList list) throws IOException {
        for (Map.Entry<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> dimEntry : list.getChunks().entrySet()) {
            if (Thread.interrupted()) {
                return;
            }
            Dimension dim = dimEntry.getKey();
            SaveCubeColumns save = saves.get(dim);
            dimEntry.getValue().parallelStream().forEach(chunksEntry -> {
                if (Thread.interrupted()) {
                    return;
                }
                try {
                    EntryLocation2D pos2d = chunksEntry.getKey();
                    IntArrayList yCoords = chunksEntry.getValue();
                    ByteBuffer column = save.load(pos2d, true).orElse(null);
                    Map<Integer, ByteBuffer> cubes = new HashMap<>();
                    for (IntCursor yCursor : yCoords) {
                        if (Thread.interrupted()) {
                            return;
                        }
                        int y = yCursor.value;
                        ByteBuffer cube = save.load(new EntryLocation3D(pos2d.getEntryX(), y, pos2d.getEntryZ()), true).orElseThrow(
                                () -> new IllegalStateException("Expected cube at " + pos2d + " at y=" + y + " in dimension " + dim));
                        cubes.put(y, cube);
                    }
                    CubicChunksColumnData data = new CubicChunksColumnData(dim, pos2d, column, cubes);
                    consumer.accept(data);
                } catch (IOException ex) {
                    throw new UncheckedIOException(ex);
                }
            });
        }
    }

    @Override public void stop() {
        loadThread.interrupt();
    }

    private static SaveCubeColumns createSave(Path path) {
        try {
            Utils.createDirectories(path);

            Path part2d = path.resolve("region2d");
            Utils.createDirectories(part2d);

            Path part3d = path.resolve("region3d");
            Utils.createDirectories(part3d);

            EntryLocation2D.Provider keyProv2d = new EntryLocation2D.Provider();
            EntryLocation3D.Provider keyProv3d = new EntryLocation3D.Provider();

            IRegionProvider<EntryLocation2D> prov2d1, prov2d2;
            IRegionProvider<EntryLocation3D> prov3d1, prov3d2;
            SaveSection2D section2d = new SaveSection2D(
                    prov2d1 = new RWLockingCachedRegionProvider<>(
                            new SimpleRegionProvider<>(keyProv2d, part2d, (keyProv, r) ->
                                    new MemoryReadRegion.Builder<EntryLocation2D>()
                                            .setDirectory(part2d)
                                            .setRegionKey(r)
                                            .setKeyProvider(keyProv2d)
                                            .setSectorSize(512)
                                            .build(),
                                    (file, key) -> Files.exists(file)
                            )
                    ),
                    prov2d2 = new RWLockingCachedRegionProvider<>(
                            new SimpleRegionProvider<>(new EntryLocation2D.Provider(), part2d,
                                    (keyProvider, regionKey) -> new ExtRegion<>(part2d, Collections.emptyList(), keyProvider, regionKey),
                                    (file, key) -> Files.exists(file.resolveSibling(key.getRegionKey().getName() + ".ext"))
                            )
                    ));
            SaveSection3D section3d = new SaveSection3D(
                    prov3d1 = new RWLockingCachedRegionProvider<>(
                            new SimpleRegionProvider<>(keyProv3d, part3d, (keyProv, r) ->
                                    new MemoryReadRegion.Builder<EntryLocation3D>()
                                            .setDirectory(part3d)
                                            .setRegionKey(r)
                                            .setKeyProvider(keyProv3d)
                                            .setSectorSize(512)
                                            .build(),
                                    (file, key) -> Files.exists(file)
                            )
                    ),
                    prov3d2 = new RWLockingCachedRegionProvider<>(
                            new SimpleRegionProvider<>(new EntryLocation3D.Provider(), part3d,
                                    (keyProvider, regionKey) -> new ExtRegion<>(part3d, Collections.emptyList(), keyProvider, regionKey),
                                    (dir, key) -> Files.exists(dir.resolveSibling(key.getRegionKey().getName() + ".ext"))
                            )
                    ));

            SaveCubeColumns saveCubeColumns = new SaveCubeColumns(section2d, section3d);
            providers2d.put(saveCubeColumns, Arrays.asList(prov2d1, prov2d2));
            providers3d.put(saveCubeColumns, Arrays.asList(prov3d1, prov3d2));
            return saveCubeColumns;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private static Vector3i toRegionPos(RegionKey key) {
        String[] split = key.getName().split("\\.");
        return new Vector3i(
                Integer.parseInt(split[0]),
                Integer.parseInt(split[1]),
                Integer.parseInt(split[2])
        );
    }

    private static class ChunkList {

        private final Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> chunks;

        private ChunkList(Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> chunks) {
            this.chunks = chunks;
        }

        Map<Dimension, List<Map.Entry<EntryLocation2D, IntArrayList>>> getChunks() {
            return chunks;
        }
    }
}
