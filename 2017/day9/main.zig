const std = @import("std");

pub fn main() !void {
    const allocator = std.heap.page_allocator;

    // Read input from standard input
    var stdin = std.io.getStdIn();
    const buffer = try stdin.reader().readAllAlloc(allocator, std.math.maxInt(usize));
    defer allocator.free(buffer);

    var score: usize = 0;
    var depth: usize = 0;
    var inGarbage = false;
    var ignoreNext = false;
    var garbageCount: usize = 0;

    for (buffer) |c| {
        if (ignoreNext) {
            ignoreNext = false;
            continue;
        }

        if (inGarbage) {
            switch (c) {
                '!' => ignoreNext = true,
                '>' => inGarbage = false,
                else => garbageCount += 1,
            }
        } else {
            switch (c) {
                '{' => {
                    depth += 1;
                    score += depth;
                },
                '}' => depth -= 1,
                '<' => inGarbage = true,
                else => {},
            }
        }
    }

    if (depth != 0 or inGarbage) {
        std.debug.print("Error: Input stream malformed\n", .{});
        return;
    }

    std.debug.print("Total score: {d}\n", .{score});
    std.debug.print("Total garbage characters: {d}\n", .{garbageCount});
}
