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
package cubicchunks.converter.lib.conf.command.arguments;

import com.mojang.brigadier.StringReader;
import com.mojang.brigadier.arguments.ArgumentType;
import com.mojang.brigadier.context.CommandContext;
import com.mojang.brigadier.exceptions.CommandSyntaxException;
import com.mojang.brigadier.suggestion.Suggestions;
import com.mojang.brigadier.suggestion.SuggestionsBuilder;
import cubicchunks.converter.lib.util.Vector3i;

import java.util.Collection;
import java.util.concurrent.CompletableFuture;

public class Vector3iArgument implements ArgumentType<Vector3i> {
    @Override
    public Vector3i parse(StringReader reader) throws CommandSyntaxException {
        return parseVector(reader);
    }

    public static Vector3i parseVector(StringReader reader) throws CommandSyntaxException {
        int i = reader.getCursor();
        int xPos = parseInt(reader);
        if (reader.canRead() && reader.peek() == ' ') {
            reader.skip();
            int yPos = parseInt(reader);
            if (reader.canRead() && reader.peek() == ' ') {
                reader.skip();
                int zPos = parseInt(reader);
                return new Vector3i(xPos, yPos, zPos);
            } else {
                reader.setCursor(i);
                throw new RuntimeException("Incomplete or invalid command!");
            }
        } else {
            reader.setCursor(i);
            throw new RuntimeException("Incomplete or invalid command!");
        }
    }

    public static int parseInt(StringReader reader) throws CommandSyntaxException {
        if (!reader.canRead()) {
            throw new RuntimeException("Expected integer got end of command!");
        } else {
            return reader.readInt();
        }
    }

    @Override
    public <S> CompletableFuture<Suggestions> listSuggestions(CommandContext<S> context, SuggestionsBuilder builder) {
        return null;
    }

    @Override
    public Collection<String> getExamples() {
        return null;
    }
}
