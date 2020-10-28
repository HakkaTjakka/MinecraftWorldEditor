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
package cubicchunks.converter.lib.convert;

import java.io.IOException;
import java.util.function.Consumer;

/**
 * Loads chunk data from input format into an in-memory representation appropriate for a specific format converter.
 */
public interface ChunkDataReader<T> extends AutoCloseable {

    /**
     * Counts chunks in the input world. This is expected to run in the background.
     *
     * @param increment Runnable to run when a new chunk is detected,
     * to increment the internal counter and update progress report
     */
    void countInputChunks(Runnable increment) throws IOException, InterruptedException;

    /**
     * Loads chunks into memory, and gives them to the provided consumer.
     * The provided consumer will block if data is provided too fast.
     */
    void loadChunks(Consumer<? super T> accept) throws IOException, InterruptedException;

    /**
     * Indicates that reading chunks should be stopped and
     * {@link #loadChunks(Consumer)} method should return.
     * Can be called from any thread.
     */
    void stop();
}
