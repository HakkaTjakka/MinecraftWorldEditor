/*
 * This file is part of nbt, licensed under the MIT License.
 *
 * Copyright (c) 2017 KyoriPowered
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
package net.kyori.nbt;

import org.checkerframework.checker.nullness.qual.NonNull;

import java.io.DataInput;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

public final class TagIO {
  private TagIO() {
  }

  /**
   * Reads a compound tag from {@code path}.
   *
   * @param path the path
   * @return the compound tag
   * @throws IOException if an exception was encountered while reading a compound tag
   */
  public static @NonNull CompoundTag readPath(final @NonNull TagTypeMap typeMap, final @NonNull Path path) throws IOException {
    return readInputStream(typeMap, Files.newInputStream(path));
  }

  /**
   * Reads a compound tag from an input stream.
   *
   * @param input the input stream
   * @return the compound tag
   * @throws IOException if an exception was encountered while reading a compound tag
   */
  public static @NonNull CompoundTag readInputStream(final @NonNull TagTypeMap typeMap, final @NonNull InputStream input) throws IOException {
    try(final DataInputStream dis = new DataInputStream(input)) {
      return readDataInput(typeMap, dis);
    }
  }

  /**
   * Reads a compound tag from {@code path} using GZIP decompression.
   *
   * @param path the path
   * @return the compound tag
   * @throws IOException if an exception was encountered while reading a compound tag
   */
  public static @NonNull CompoundTag readCompressedPath(final @NonNull TagTypeMap typeMap, final @NonNull Path path) throws IOException {
    return readCompressedInputStream(typeMap, Files.newInputStream(path));
  }

  /**
   * Reads a compound tag from an input stream using GZIP decompression.
   *
   * @param input the input stream
   * @return the compound tag
   * @throws IOException if an exception was encountered while reading a compound tag
   */
  public static @NonNull CompoundTag readCompressedInputStream(final @NonNull TagTypeMap typeMap, final @NonNull InputStream input) throws IOException {
    try(final DataInputStream dis = new DataInputStream(new GZIPInputStream(input))) {
      return readDataInput(typeMap, dis);
    }
  }

  /**
   * Reads a compound tag from {@code input}.
   *
   * @param input the input
   * @return the compound tag
   * @throws IOException if an exception was encountered while reading a compound tag
   */
  public static @NonNull CompoundTag readDataInput(final @NonNull TagTypeMap typeMap, final @NonNull DataInput input) throws IOException {
    final TagType type = typeMap.fromId(input.readByte());
    if(type != TagType.COMPOUND) {
      throw new IOException(String.format("Expected root tag to be a %s, was %s", TagType.COMPOUND, type));
    }
    input.skipBytes(input.readUnsignedShort()); // read empty name
    final Tag tag = type.create();
    tag.read(typeMap, input, 0); // initial depth is zero
    return (CompoundTag) tag;
  }

  /**
   * Writes a compound tag to {@code path}.
   *
   * @param tag the compound tag
   * @param path the path
   * @throws IOException if an exception was encountered while writing the compound tag
   */
  public static void writePath(final @NonNull TagTypeMap typeMap, final @NonNull CompoundTag tag, final @NonNull Path path) throws IOException {
    writeOutputStream(typeMap, tag, Files.newOutputStream(path));
  }

  /**
   * Writes a compound tag to an output stream.
   *
   * @param tag the compound tag
   * @param output the output stream
   * @throws IOException if an exception was encountered while writing the compound tag
   */
  public static void writeOutputStream(final @NonNull TagTypeMap typeMap, final @NonNull CompoundTag tag, final @NonNull OutputStream output) throws IOException {
    try(final DataOutputStream dos = new DataOutputStream(output)) {
      writeDataOutput(typeMap, tag, dos);
    }
  }

  /**
   * Writes a compound tag to {@code path} using GZIP compression.
   *
   * @param tag the compound tag
   * @param path the path
   * @throws IOException if an exception was encountered while writing the compound tag
   */
  public static void writeCompressedPath(final @NonNull TagTypeMap typeMap, final @NonNull CompoundTag tag, final @NonNull Path path) throws IOException {
    writeCompressedOutputStream(typeMap, tag, Files.newOutputStream(path));
  }

  /**
   * Writes a compound tag to an output stream using GZIP compression.
   *
   * @param tag the compound tag
   * @param output the output stream
   * @throws IOException if an exception was encountered while writing the compound tag
   */
  public static void writeCompressedOutputStream(final @NonNull TagTypeMap typeMap, final @NonNull CompoundTag tag, final @NonNull OutputStream output) throws IOException {
    try(final DataOutputStream dos = new DataOutputStream(new GZIPOutputStream(output))) {
      writeDataOutput(typeMap, tag, dos);
    }
  }

  /**
   * Writes a compound tag to {@code output}.
   *
   * @param tag the compound tag
   * @param output the output
   * @throws IOException if an exception was encountered while writing the compound tag
   */
  public static void writeDataOutput(final @NonNull TagTypeMap typeMap, final @NonNull CompoundTag tag, final @NonNull DataOutput output) throws IOException {
    output.writeByte(typeMap.getId(tag.type()));
    if(tag.type() != TagType.END) {
      output.writeUTF(""); // write empty name
      tag.write(typeMap, output);
    }
  }
}
