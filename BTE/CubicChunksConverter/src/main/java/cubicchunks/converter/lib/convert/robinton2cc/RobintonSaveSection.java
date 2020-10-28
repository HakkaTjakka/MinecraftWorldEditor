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

import cubicchunks.converter.lib.util.RWLockingCachedRegionProvider;
import cubicchunks.regionlib.api.region.IRegionProvider;
import cubicchunks.regionlib.api.storage.SaveSection;
import cubicchunks.regionlib.lib.Region;
import cubicchunks.regionlib.lib.provider.SharedCachedRegionProvider;
import cubicchunks.regionlib.lib.provider.SimpleRegionProvider;

import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Collections;

public class RobintonSaveSection extends SaveSection<RobintonSaveSection, RobintonEntryLocation3D> {

    public static final Object EMPTY_MARKER = "Empty cube marker";
    public static final ByteBuffer EMPTY_BUFFER = ByteBuffer.wrap(new byte[0]);

    /**
     * Creates a 3D save section with a customized IRegionProvider
     *
     * @param regionProvider The region provider
     */
    public RobintonSaveSection(IRegionProvider<RobintonEntryLocation3D> regionProvider) {
        super(Collections.singletonList(regionProvider));
    }

    public static RobintonSaveSection createAt(Path directory) {
        return new RobintonSaveSection(new RWLockingCachedRegionProvider<>(
                new SimpleRegionProvider<>(new RobintonEntryLocation3D.Provider(), directory, (keyProv, r) ->
                        new Region.Builder<RobintonEntryLocation3D>()
                                .addSpecialSectorMapEntry(EMPTY_MARKER, 0xFFFFFFFF, loc -> EMPTY_BUFFER, RobintonSaveSection::throwingErrorHandler)
                                .setDirectory(directory)
                                .setRegionKey(r)
                                .setKeyProvider(keyProv)
                                .setSectorSize(256)
                                .build(),
                        (dir, key) -> Files.exists(dir.resolve(key.getRegionKey().getName()))
                )
        ));
    }

    private static void throwingErrorHandler(RobintonEntryLocation3D loc, ByteBuffer buf) {
        throw new IllegalStateException("Robinton's cubic chunks format doesn't support writing "
                + "cube data with region header entry 0xFFFFFFFF ");
    }
}
