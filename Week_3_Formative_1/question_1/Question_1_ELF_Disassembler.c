#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path_to_elf_file>\n", argv[0]);
        return 1;
    }

    char *elf_path = argv[1];
    char output_file[512];
    char command[1024];

    // Check if file exists
    if (access(elf_path, F_OK) != 0) {
        printf("Error: File '%s' does not exist.\n", elf_path);
        return 1;
    }

    // Safely construct output filename
    int len = snprintf(output_file, sizeof(output_file), "%s_disassembled.txt", elf_path);
    if (len < 0 || (size_t)len >= sizeof(output_file)) {
        printf("Error: Output filename too long.\n");
        return 1;
    }

    // Safely construct command with proper quoting to prevent command injection
    len = snprintf(command, sizeof(command), "objdump -d -j .text '%s' > '%s'", elf_path, output_file);
    if (len < 0 || (size_t)len >= sizeof(command)) {
        printf("Error: Command string too long.\n");
        return 1;
    }

    int result = system(command);

    if (result == 0) {
        printf("Disassembly successful!\n");
        printf("Output saved to: %s\n", output_file);
    } else {
        printf("Error: Failed to disassemble the file.\n");
        printf("Make sure the file is a valid ELF binary.\n");
        return 1;
    }

    return 0;
}
