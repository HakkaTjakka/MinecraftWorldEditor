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
package cubicchunks.converter.lib.conf.command.commands;

import com.mojang.brigadier.CommandDispatcher;
import com.mojang.brigadier.builder.LiteralArgumentBuilder;
import com.mojang.brigadier.builder.RequiredArgumentBuilder;
import cubicchunks.converter.lib.conf.command.EditTaskContext;
import cubicchunks.converter.lib.conf.command.arguments.BoundingBoxArgument;
import cubicchunks.converter.lib.conf.command.arguments.Vector3iArgument;
import cubicchunks.converter.lib.util.BoundingBox;
import cubicchunks.converter.lib.util.EditTask;
import cubicchunks.converter.lib.util.Vector3i;

public class CopyCommand {
    public static void register(CommandDispatcher<EditTaskContext> dispatcher) {
        dispatcher.register(LiteralArgumentBuilder.<EditTaskContext>literal("copy")
            .then(RequiredArgumentBuilder.<EditTaskContext, BoundingBox>argument("box", new BoundingBoxArgument())
                .then(LiteralArgumentBuilder.<EditTaskContext>literal("to")
                    .then(RequiredArgumentBuilder.<EditTaskContext, Vector3i>argument("dst", new Vector3iArgument())
                        .executes((info) -> {
                            BoundingBox box = info.getArgument("box", BoundingBox.class);
                            info.getSource().addEditTask(new EditTask(
                                box,
                                info.getArgument("dst", Vector3i.class).sub(box.getMinPos()),
                                EditTask.Type.COPY
                            ));
                            return 1;
                        })
                    )
                ).then(LiteralArgumentBuilder.<EditTaskContext>literal("by")
                    .then(RequiredArgumentBuilder.<EditTaskContext, Vector3i>argument("dst", new Vector3iArgument())
                        .executes((info) -> {
                            info.getSource().addEditTask(new EditTask(
                                info.getArgument("box", BoundingBox.class),
                                info.getArgument("dst", Vector3i.class),
                                EditTask.Type.COPY
                            ));
                            return 1;
                        })
                    )
                )
            )
        );
    }
}
