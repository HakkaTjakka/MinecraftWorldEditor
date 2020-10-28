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
package net.kyori.nbt.display;

import net.kyori.nbt.ByteArrayTag;
import net.kyori.nbt.ByteTag;
import net.kyori.nbt.CompoundTag;
import net.kyori.nbt.DoubleTag;
import net.kyori.nbt.EndTag;
import net.kyori.nbt.FloatTag;
import net.kyori.nbt.IntArrayTag;
import net.kyori.nbt.IntTag;
import net.kyori.nbt.ListTag;
import net.kyori.nbt.LongArrayTag;
import net.kyori.nbt.LongTag;
import net.kyori.nbt.ShortTag;
import net.kyori.nbt.StringTag;
import net.kyori.nbt.Tag;
import org.checkerframework.checker.nullness.qual.NonNull;
import org.checkerframework.checker.nullness.qual.Nullable;

import java.util.Collections;
import java.util.Iterator;
import java.util.regex.Pattern;

/**
 * A tag displayer that renders a {@link Tag} into a {@link String}.
 */
public class StringTagDisplay implements TagDisplay<String> {
  private static final Pattern SIMPLE_VALUE = Pattern.compile("[a-zA-Z0-9._+-]+");

  @Override
  public @NonNull String render(final @NonNull Tag tag) {
    final StringBuilder sb = new StringBuilder();
    this.render(tag, sb);
    return sb.toString();
  }

  public void render(final @NonNull Tag tag, final @NonNull StringBuilder sb) {
    this.render(null, tag, sb, 0);
  }

  private void render(final @Nullable String name, final Tag tag, final StringBuilder sb, final int depth) {
    if(tag instanceof CompoundTag) {
      this.indent(sb, depth);

      if(name != null) {
        sb.append(name).append(' ');
      }

      sb.append('{');
      sb.append('\n');

      for(final Iterator<String> iterator = ((CompoundTag) tag).keySet().iterator(); iterator.hasNext(); ) {
        final String key = iterator.next();
        final Tag value = ((CompoundTag) tag).get(key);
        this.render(key, value, sb, depth + 1);
        if(iterator.hasNext()) {
          sb.append(',').append('\n');
        }
      }

      sb.append('\n');
      this.indent(sb, depth);
      sb.append('}');
    } else if(tag instanceof ListTag) {
      this.indent(sb, depth);

      if(name != null) {
        sb.append(name).append(' ');
      }

      sb.append('[');

      if(!((ListTag) tag).isEmpty()) {
        sb.append('\n');

        for(int i = 0, size = ((ListTag) tag).size(); i < size; i++) {
          final Tag child = ((ListTag) tag).get(i);
          this.render(null, child, sb, depth + 1);
          if(i + 1 < size) {
            sb.append(',').append('\n');
          }
        }

        sb.append('\n');
        this.indent(sb, depth);
      }

      sb.append(']');
    } else {
      this.indent(sb, depth);

      if(name != null) {
        sb.append(name).append('=');
      }

      sb.append(toString(tag));
    }
  }

  private void indent(final StringBuilder sb, final int depth) {
    sb.append(String.join("", Collections.nCopies(depth, "    ")));
  }

  private static String toString(final Tag tag) {
    if(tag instanceof ByteArrayTag) {
      final StringBuilder sb = new StringBuilder("[B;");
      for(int i = 0, length = ((ByteArrayTag) tag).value().length; i < length; ++i) {
        if(i != 0) {
          sb.append(',');
        }
        sb.append(((ByteArrayTag) tag).value()[i]).append('B');
      }
      return sb.append(']').toString();
    } else if(tag instanceof ByteTag) {
      return String.valueOf(((ByteTag) tag).byteValue());
    } else if(tag instanceof CompoundTag) {
      final StringBuilder sb = new StringBuilder("{");
      for(final String key : ((CompoundTag) tag).keySet()) {
        if(sb.length() != 1) {
          sb.append(',');
        }
        sb.append(renderKey(key)).append(':').append(((CompoundTag) tag).get(key));
      }
      return sb.append('}').toString();
    } else if(tag instanceof DoubleTag) {
      return ((DoubleTag) tag).doubleValue() + "d";
    } else if(tag instanceof EndTag) {
      return "";
    } else if(tag instanceof FloatTag) {
      return ((FloatTag) tag).floatValue() + "f";
    } else if(tag instanceof IntArrayTag) {
      final StringBuilder sb = new StringBuilder("[I;");
      for(int i = 0; i < ((IntArrayTag) tag).value().length; ++i) {
        if(i != 0) {
          sb.append(',');
        }
        sb.append(((IntArrayTag) tag).value()[i]);
      }
      return sb.append(']').toString();
    } else if(tag instanceof IntTag) {
      return String.valueOf(((IntTag) tag).intValue());
    } else if(tag instanceof ListTag) {
      final StringBuilder sb = new StringBuilder("[");
      for(int i = 0; i < ((ListTag) tag).size(); ++i) {
        if(i != 0) {
          sb.append(',');
        }
        sb.append(((ListTag) tag).get(i));
      }
      return sb.append(']').toString();
    } else if(tag instanceof LongArrayTag) {
      final StringBuilder sb = new StringBuilder("[L;");
      for(int i = 0; i < ((LongArrayTag) tag).value().length; ++i) {
        if(i != 0) {
          sb.append(',');
        }
        sb.append(((LongArrayTag) tag).value()[i]).append('L');
      }
      return sb.append(']').toString();
    } else if(tag instanceof LongTag) {
      return ((LongTag) tag).longValue() + "L";
    } else if(tag instanceof ShortTag) {
      return ((ShortTag) tag).shortValue() + "s";
    } else if(tag instanceof StringTag) {
      return renderQuotedString(((StringTag) tag).value());
    }
    throw new IllegalArgumentException(tag.getClass().getName());
  }

  private static String renderKey(final String string) {
    if(SIMPLE_VALUE.matcher(string).matches()) {
      return string;
    }
    return renderQuotedString(string);
  }

  private static String renderQuotedString(final String string) {
    final StringBuilder sb = new StringBuilder();
    sb.append('"');
    for(int i = 0; i < string.length(); ++i) {
      final char c = string.charAt(i);
      if(c == '\\' || c == '"') {
        sb.append('\\');
      }
      sb.append(c);
    }
    sb.append('"');
    return sb.toString();
  }
}
