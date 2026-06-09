*This project has been created as part of the 42 curriculum by kobadai.*

# get_next_line

## Description

`get_next_line` is a 42 curriculum project whose goal is to implement a
function that returns one line at a time from a file descriptor.

The function keeps unread data between calls with a static variable, so repeated
calls continue from the previous position until the end of the file or an error
is reached.

### Features

- Reads from a valid file descriptor, including files and standard input.
- Returns each line with its terminating newline character when one exists.
- Supports custom buffer sizes with `-D BUFFER_SIZE=n`.
- Provides a default `BUFFER_SIZE` value when the macro is not defined.
- Returns `NULL` when there is nothing left to read, an error occurs, or
  `BUFFER_SIZE <= 0`.
- Bonus version tracks multiple file descriptors at the same time.

## Instructions

### Compilation

Mandatory part:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Bonus part:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

The project can also be compiled without `-D BUFFER_SIZE=...`; in that case,
the header defines a default value.

### Usage Example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Each returned line is allocated with `malloc`, so the caller must free it.

### Bonus Usage Example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

static void	print_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line != NULL)
	{
		printf("%s", line);
		free(line);
	}
}

int	main(void)
{
	int	fd1;
	int	fd2;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	print_line(fd1);
	print_line(fd2);
	print_line(fd1);
	print_line(fd2);
	close(fd1);
	close(fd2);
	return (0);
}
```

## Algorithm Explanation

This implementation stores the current reading state in a `t_gnl` structure:

- `data`: dynamically allocated buffer containing unread data.
- `len`: number of bytes currently stored in `data`.
- `cap`: allocated capacity of `data`.

The mandatory version uses one static `t_gnl *state`. The bonus version uses one
static variable, `t_gnl *state[OPEN_MAX]`, so each file descriptor has its own
independent state.

The algorithm follows this cycle:

1. Initialize the state when `get_next_line` is called for the first time.
2. Read `BUFFER_SIZE` bytes at a time and append them to `state->data`.
3. Stop reading as soon as a newline is already stored, EOF is reached, or an
   error occurs.
4. Allocate and return a new string containing the next complete line.
5. Move the unread remainder to the beginning of `state->data` for the next
   call.
6. Free the state when EOF is reached or when an error occurs.

This approach avoids reading the whole file at once. The buffer capacity grows
only when needed, which allows the function to handle both small and large lines
while keeping the number of allocations controlled.

## Resources

- 42 get_next_line subject PDF.
- [1時間で書くGet Next Line(GNL)](https://zenn.dev/grigri_grin/articles/bf45a9fa50f25f)
- [get_next_line（42課題備忘録）gnl](https://koisuru-computer.hateblo.jp/entry/9937063)
- `man 2 read`
- `man 3 malloc`
- C documentation about static variables and file descriptors.

## AI Usage Disclosure

AI assistance was used for:

- Reviewing edge cases such as `BUFFER_SIZE=1`, `BUFFER_SIZE=0`, and
  `BUFFER_SIZE=-1`.
- Checking the README structure against the project requirements.
- Clarifying the written explanation of the algorithm.

The implementation logic and final code were checked against the local source
files and tested with compiler, Norm, and memory-leak checks.

# get_next_line (Japanese)

## 概要

`get_next_line` は、ファイルディスクリプタから1行ずつ文字列を読み取って
返す関数を実装する42課題です。

この実装では、読み残したデータを static 変数に保存します。そのため、
`get_next_line` を繰り返し呼ぶことで、前回の続きから1行ずつ読み進められます。

### 主な機能

- ファイルや標準入力など、有効なファイルディスクリプタから読み取る。
- 改行が存在する場合は、返り値に `\n` を含める。
- `-D BUFFER_SIZE=n` によって読み取りサイズを変更できる。
- `BUFFER_SIZE` が指定されない場合は、ヘッダ内のデフォルト値を使う。
- EOF、エラー、または `BUFFER_SIZE <= 0` の場合は `NULL` を返す。
- bonus 版では、複数の fd を同時に管理できる。

## 使用方法

mandatory:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

bonus:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

返された文字列は `malloc` で確保されているため、呼び出し側で `free` します。



## アルゴリズムの説明

この実装では `t_gnl` 構造体で読み取り状態を管理しています。

- `data`: 読み残しを保存する動的バッファ。
- `len`: 現在 `data` に入っているバイト数。
- `cap`: `data` に確保済みの容量。

mandatory 版では `static t_gnl *state` を使います。bonus 版では
`static t_gnl *state[OPEN_MAX]` を使い、fd 番号を配列のインデックスにすることで、
fd ごとに独立した読み取り状態を保存します。

処理の流れは次の通りです。

1. 初回呼び出し時に state を初期化する。
2. `BUFFER_SIZE` バイトずつ読み取り、`state->data` に追加する。
3. 改行、EOF、エラーのいずれかに到達したら読み取りを止める。
4. 次に返す1行分だけを新しく確保して返す。
5. 返した行の後ろに残ったデータを先頭へ詰め、次回呼び出しに備える。
6. EOF またはエラー時には state を解放する。

この方法により、ファイル全体を一度に読み込まず、必要な分だけ読み取れます。
また、バッファ容量は必要になったときだけ拡張されるため、短い行にも長い行にも
対応しやすい構成になっています。
