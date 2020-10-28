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
package cubicchunks.converter.lib.convert.cc2anvil;

import com.flowpowered.nbt.CompoundMap;
import com.flowpowered.nbt.CompoundTag;
import com.flowpowered.nbt.StringTag;
import com.flowpowered.nbt.Tag;
import com.flowpowered.nbt.stream.NBTInputStream;
import com.flowpowered.nbt.stream.NBTOutputStream;
import cubicchunks.converter.lib.Dimensions;
import cubicchunks.converter.lib.util.Utils;
import cubicchunks.converter.lib.convert.LevelInfoConverter;
import cubicchunks.converter.lib.convert.data.CubicChunksColumnData;
import cubicchunks.converter.lib.convert.data.MultilayerAnvilChunkData;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class CC2AnvilLevelInfoConverter implements LevelInfoConverter<CubicChunksColumnData, MultilayerAnvilChunkData> {

    private final Path srcPath;
    private final Path dstPath;

    public CC2AnvilLevelInfoConverter(Path srcPath, Path dstPath) {
        this.srcPath = srcPath;
        this.dstPath = dstPath;
    }

    @Override public void convert() throws IOException {
        Utils.forEachDirectory(dstPath, dir -> {
            CompoundTag root;
            try (NBTInputStream nbtIn = new NBTInputStream(Files.newInputStream(srcPath.resolve("level.dat")));
                NBTOutputStream nbtOut = new NBTOutputStream(Files.newOutputStream(dir.resolve("level.dat")))) {
                root = (CompoundTag) nbtIn.readTag();

                CompoundMap newRoot = new CompoundMap();
                for (Tag<?> tag : root.getValue()) {
                    if (tag.getName().equals("Data")) {
                        CompoundTag data = (CompoundTag) tag;
                        CompoundMap newDataMap = new CompoundMap();
                        for (Tag<?> dataTag : data.getValue()) {
                            if (dataTag.getName().equals("isCubicWorld")) {
                                continue;
                            }
                            if (dataTag.getName().equalsIgnoreCase("generatorName")) {
                                newDataMap.put(new StringTag(dataTag.getName(), getGeneratorName((String) dataTag.getValue())));
                            } else {
                                newDataMap.put(dataTag);
                            }
                        }
                        newRoot.put(new CompoundTag("Data", newDataMap));
                    } else {
                        newRoot.put(tag);
                    }
                }
                Files.createDirectories(dir);

                nbtOut.writeTag(new CompoundTag(root.getName(), newRoot));

                Utils.copyEverythingExcept(srcPath, srcPath, dir, file ->
                        file.toString().contains("level.dat") || file.toString().endsWith("custom_generator_settings.json")
                                || file.toString().endsWith("cubicChunksData.dat") || file.toString().endsWith("cubicchunks_spawncubes.dat") ||
                            Dimensions.getDimensions().stream().anyMatch(dim ->
                                srcPath.resolve(dim.getDirectory()).resolve("region2d").equals(file)
                                    || srcPath.resolve(dim.getDirectory()).resolve("region3d").equals(file)
                            ),
                    f -> {
                    } // TODO: counting files
                );
            }
        });
    }

    private String getGeneratorName(String value) {
        switch (value) {
            case "CustomCubic":
            case "VanillaCubic":
                return "default";
            case "FlatCubic":
                return "flat";
            default:
                return value;
        }
    }
}
