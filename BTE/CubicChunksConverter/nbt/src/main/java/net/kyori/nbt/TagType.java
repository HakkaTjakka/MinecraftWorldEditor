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

import java.util.function.Predicate;
import java.util.function.Supplier;

/**
 * An enumeration of tag types.
 */
public enum TagType implements Predicate<TagType> {
  /**
   * @see EndTag
   */
  END(EndTag::new),
  /**
   * @see ByteTag
   */
  BYTE(true, ByteTag::new),
  /**
   * @see ShortTag
   */
  SHORT(true, ShortTag::new),
  /**
   * @see IntTag
   */
  INT(true, IntTag::new),
  /**
   * @see LongTag
   */
  LONG(true, LongTag::new),
  /**
   * @see FloatTag
   */
  FLOAT(true, FloatTag::new),
  /**
   * @see DoubleTag
   */
  DOUBLE(true, DoubleTag::new),
  /**
   * @see ByteArrayTag
   */
  BYTE_ARRAY(ByteArrayTag::new),
  /**
   * @see StringTag
   */
  STRING(StringTag::new),
  /**
   * @see ListTag
   */
  LIST(ListTag::new),
  /**
   * @see CompoundTag
   */
  COMPOUND(CompoundTag::new),
  /**
   * @see IntArrayTag
   */
  INT_ARRAY(IntArrayTag::new),
  /**
   * @see LongArrayTag
   */
  LONG_ARRAY(LongArrayTag::new),
  /**
   * @see ShortArrayTag
   */
  SHORT_ARRAY(ShortArrayTag::new);

  private static final TagType[] TYPES = values();

  /**
   * If this tag type is a {@link NumberTag number} type.
   */
  private final boolean number;
  /**
   * The tag factory.
   */
  private final @NonNull Supplier<Tag> factory;

  TagType(final @NonNull Supplier<Tag> factory) {
    this(false, factory);
  }

  TagType(final boolean number, final @NonNull Supplier<Tag> factory) {
    this.number = number;
    this.factory = factory;
  }

  /**
   * Checks if this tag type is a {@link NumberTag number} type.
   *
   * @return {@code true} if a number type, {@code false} if not
   */
  public boolean number() {
    return this.number;
  }

  /**
   * Creates a new tag.
   *
   * @return a new tag
   */
  @NonNull Tag create() {
    return this.factory.get();
  }

  public boolean test(final @NonNull TagType that) {
    return this == that || (this.number && that.number);
  }
}
