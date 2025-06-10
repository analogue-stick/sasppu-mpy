# Color manipulation macros
def grey555(g: int) -> int: ...
def grey555_cmath(g: int) -> int: ...
def rgb555(r: int, g: int, b: int) -> int: ...
def rgb555_cmath(r: int, g: int, b: int) -> int: ...
def rgb888(r: int, g: int, b: int) -> int: ...
def rgb888_cmath(r: int, g: int, b: int) -> int: ...
def mul_rgb555(r: int, g: int, b: int, mul: int) -> int: ...
def mul_col(col: int, mul: int) -> int: ...
def r_channel(col: int) -> int: ...
def g_channel(col: int) -> int: ...
def b_channel(col: int) -> int: ...
def cmath_channel(col: int) -> int: ...

# Predefined colors
TRANSPARENT_BLACK: int
OPAQUE_BLACK: int
RED: int
GREEN: int
BLUE: int
WHITE: int

# Image codes
class ImageCode:
    Success: int
    TooWide: int
    TooTall: int
    InvalidBitdepth: int

# Sprite functions
def copy_sprite(
    dst_x: int,
    dst_y: int,
    width: int,
    height: int,
    src_x: int,
    src_y: int,
    double_size: bool,
) -> int: ...
def copy_sprite_transparent(
    dst_x: int,
    dst_y: int,
    width: int,
    height: int,
    src_x: int,
    src_y: int,
    double_size: bool,
) -> int: ...
def blit_sprite(
    x: int, y: int, width: int, height: int, double_size: bool, data: bytes
) -> int: ...
def blit_sprite_transparent(
    x: int, y: int, width: int, height: int, double_size: bool, data: bytes
) -> int: ...
def paletted_sprite(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def paletted_sprite_transparent(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def compressed_sprite(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def compressed_sprite_transparent(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def fill_sprite(x: int, y: int, width: int, height: int, colour: int) -> int: ...
def draw_text_sprite(
    x: int,
    y: int,
    colour: int,
    line_width: int,
    newline_height: int,
    double_size: bool,
    text: str,
) -> int: ...
def draw_text_next_sprite(
    x: int,
    y: int,
    colour: int,
    line_start: int,
    line_width: int,
    newline_height: int,
    double_size: bool,
    text: str,
) -> int: ...

# Background functions
def copy_background(
    dst_x: int,
    dst_y: int,
    width: int,
    height: int,
    src_x: int,
    src_y: int,
    double_size: bool,
) -> int: ...
def copy_background_transparent(
    dst_x: int,
    dst_y: int,
    width: int,
    height: int,
    src_x: int,
    src_y: int,
    double_size: bool,
) -> int: ...
def blit_background(
    x: int, y: int, width: int, height: int, double_size: bool, data: bytes
) -> int: ...
def blit_background_transparent(
    x: int, y: int, width: int, height: int, double_size: bool, data: bytes
) -> int: ...
def paletted_background(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def paletted_background_transparent(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def compressed_background(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def compressed_background_transparent(
    x: int,
    y: int,
    width: int,
    height: int,
    double_size: bool,
    data: bytes,
    palette: bytes,
    bitdepth: int,
) -> int: ...
def fill_background(x: int, y: int, width: int, height: int, colour: int) -> int: ...
def draw_text_background(
    x: int,
    y: int,
    colour: int,
    line_width: int,
    newline_height: int,
    double_size: bool,
    text: str,
) -> int: ...
def draw_text_next_background(
    x: int,
    y: int,
    colour: int,
    line_start: int,
    line_width: int,
    newline_height: int,
    double_size: bool,
    text: str,
) -> int: ...

# Utility functions
def get_text_size(
    line_width: int, newline_height: int, double_size: bool, text: str
) -> tuple[int, int]: ...
def gfx_reset() -> None: ...
