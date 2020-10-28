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
import static cubicchunks.regionlib.impl.save.MinecraftSaveSection.MinecraftRegionType.MCA;
import static java.nio.file.Files.exists;

import cubicchunks.converter.lib.Dimension;
import cubicchunks.converter.lib.convert.data.AnvilChunkData;
import cubicchunks.converter.lib.util.MemoryReadRegion;
import cubicchunks.converter.lib.util.RWLockingCachedRegionProvider;
import cubicchunks.converter.lib.util.UncheckedInterruptedException;
import cubicchunks.regionlib.impl.MinecraftChunkLocation;
import cubicchunks.regionlib.impl.header.TimestampHeaderEntryProvider;
import cubicchunks.regionlib.impl.save.MinecraftSaveSection;
import cubicchunks.regionlib.lib.provider.SimpleRegionProvider;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;
import java.util.concurrent.TimeUnit;
import java.util.function.Consumer;

public class AnvilChunkReader extends BaseMinecraftReader<AnvilChunkData, MinecraftSaveSection> {

    private final Thread loadThread;

    public AnvilChunkReader(Path srcDir) {
        super(srcDir, (dim, path) -> exists(getDimensionPath(dim, path)) ? createSave(dim, path) : null);
        loadThread = Thread.currentThread();
    }

    private static MinecraftSaveSection createSave(Dimension dim, Path path) {
        Path directory = getDimensionPath(dim, path);
        return new MinecraftSaveSection(new RWLockingCachedRegionProvider<>(
                new SimpleRegionProvider<>(new MinecraftChunkLocation.Provider(MCA.name().toLowerCase()), directory, (keyProvider, regionKey) ->
                        MemoryReadRegion.<MinecraftChunkLocation>builder()
                                .setDirectory(directory)
                                .setSectorSize(4096)
                                .setKeyProvider(keyProvider)
                                .setRegionKey(regionKey)
                                .addHeaderEntry(new TimestampHeaderEntryProvider<>(TimeUnit.MILLISECONDS))
                                .build(),
                        (file, key) -> Files.exists(file)
                )
        ));
    }

    private static Path getDimensionPath(Dimension d, Path worldDir) {
        if (!d.getDirectory().isEmpty()) {
            worldDir = worldDir.resolve(d.getDirectory());
        }
        return worldDir.resolve("region");
    }

    @Override public void countInputChunks(Runnable increment) throws IOException {
        try {
            doCountChunks(increment);
        } catch (UncheckedInterruptedException ex) {
            // return
        }
    }

    private void doCountChunks(Runnable increment) throws IOException, UncheckedInterruptedException {
        for (MinecraftSaveSection save : saves.values()) {
            save.forAllKeys(interruptibleConsumer(loc -> increment.run()));
        }
    }

    @Override public void loadChunks(Consumer<? super AnvilChunkData> consumer) throws IOException {
        try {
            doLoadChunks(consumer);
        } catch (UncheckedInterruptedException ex) {
            // return
        }
    }

    private void doLoadChunks(Consumer<? super AnvilChunkData> consumer) throws IOException, UncheckedInterruptedException {
        for (Map.Entry<Dimension, MinecraftSaveSection> entry : saves.entrySet()) {
            if (Thread.interrupted()) {
                return;
            }
            MinecraftSaveSection vanillaSave = entry.getValue();
            Dimension d = entry.getKey();
            vanillaSave.forAllKeys(interruptibleConsumer(mcPos -> consumer.accept(new AnvilChunkData(d, mcPos, vanillaSave.load(mcPos, true).orElse(null)))));
        }
    }

    @Override public void stop() {
        loadThread.interrupt();
    }

}
