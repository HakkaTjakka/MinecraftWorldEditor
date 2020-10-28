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
package cubicchunks.converter.lib.convert.robinton2cc;

import cubicchunks.converter.lib.convert.LevelInfoConverter;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.convert.data.RobintonColumnData;
import net.kyori.nbt.CompoundTag;
import net.kyori.nbt.TagIO;
import net.kyori.nbt.TagTypeMaps;

import java.io.IOException;
import java.nio.file.Path;

public class Robinton2CCLevelInfoConverter implements LevelInfoConverter<RobintonColumnData, CubicChunksColumnData> {
    private final Path srcPath;
    private final Path dstPath;

    public Robinton2CCLevelInfoConverter(Path srcPath, Path dstPath) {
        this.srcPath = srcPath;
        this.dstPath = dstPath;
    }

    @Override public void convert() throws IOException {
        CompoundTag srcTag = TagIO.readCompressedPath(TagTypeMaps.ROBINTON, srcPath.resolve("level.dat"));
        CompoundTag dstTag = new CompoundTag();

        convertTag(srcTag, dstTag);

        TagIO.writeCompressedPath(TagTypeMaps.MINECRAFT, dstTag, dstPath.resolve("level.dat"));
    }

    private void convertTag(CompoundTag srcTag, CompoundTag dstTag) {
        /*

        1.2.5 format:
        ROOT
        |- Data
         |- RandomSeed: 7883083885319635152L +
         |- generatorName: default +
         |- SpawnY: 64 +
         |- rainTime: 33399 -- skipped
         |- thunderTime: 73473 -- skipped
         |- SpawnZ: 140 +
         |- hardcore: 0B -- skipped
         |- SpawnX: 208 +
         |- raining: 0B -- skipped
         |- Time: 2856L +
         |- thundering: 0B -- skipped
         |- GameType: 1 -- skipped
         |- generatorVersion: 1 +
         |- MapFeatures: 1B +
         |- version: 19133 +
         |- LastPlayed: 1566327322121L +
         |- LevelName: "1.2.5-getleveldat" +
         |- SizeOnDisk: 0L +
         |- Player +
          |- ... - moved as is

        Old format:
        ROOT
        |- Data
         |- LastPlayed (long) +
         |- RandomSeed (long) +
         |- Player +
          |- ...
         |- SpawnX +
         |- SpawnY +
         |- SpawnZ +
         |- Time (long) +
         |- YLimit (int) - ignored
         |- SizeOnDisk (long) +
         */
        CompoundTag dstData = new CompoundTag();
        CompoundTag srcData = srcTag.getCompound("Data");
        dstData.putBoolean("isCubicWorld", true);
        dstData.putString("generatorName", "CustomCubic");
        dstData.putInt("generatorVersion", 1);
        dstData.putBoolean("MapFeatures", true);
        dstData.putInt("version", 19133); // marks this world as MC 1.2.x anvil world
        dstData.putString("LevelName", srcPath.getFileName().toString());
        // workaround for cubic chunks bug, spawn chunks are generated before MC sets difficulty on world load, causing crash
        dstData.putByte("Difficulty", (byte) 2); // set to normal

        dstData.putLong("RandomSeed", srcData.getLong("RandomSeed"));
        dstData.putLong("Time", srcData.getLong("Time"));
        dstData.putLong("SizeOnDisk", srcData.getLong("SizeOnDisk"));
        dstData.putInt("SpawnX", srcData.getInt("SpawnX"));
        dstData.putInt("SpawnY", srcData.getInt("SpawnY"));
        dstData.putInt("SpawnZ", srcData.getInt("SpawnZ"));
        dstData.putLong("LastPlayed", srcData.getLong("LastPlayed"));
        dstData.put("Player", srcData.getCompound("Player"));

        dstTag.put("Data", dstData);
    }
}
