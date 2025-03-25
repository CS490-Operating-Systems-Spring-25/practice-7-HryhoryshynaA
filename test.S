.section .data
    message:
        .asciz "Hello!\n"

    buffer: 
        .fill 256, 1, 0

    filename:
        .asciz "testfile.txt"

    newline:
        .asciz "\n"

    file_content:
        .asciz "This is a test.\n"

.section .text
    .global _start

    _start:
        // Print Hello!
        mov x0, #1
        ldr x1, =message
        mov x2, #7
        mov x8, #64
        svc #0

        // get current directory
        ldr x0, =buffer
        mov x1, #256
        mov x8, #17
        svc #0

        // print current directory
        mov x0, #1
        ldr x1, =buffer
        mov x2, #256
        mov x8, #64
        svc #0

        // print newline
        mov x0, #1
        ldr x1, =newline
        mov x2, #1
        mov x8, #64
        svc #0

        // create and open a file
        mov x0, #-100
        ldr x1, =filename
        mov x2, #0x241
        mov x3, #0644
        mov x8, #56
        svc #0
        mov x9, x0

        // write to the file
        mov x0, x9
        ldr x1, =file_content
        mov x2, #16
        mov x8, #64
        svc #0

        // close the file
        mov x0, x9
        mov x8, #57
        svc #0

        // change file permissions - syscall 52: chmod
        ldr x0, =filename
        mov x1, #0755
        mov x8, #52
        svc #0

        // set user ID - setuid
        mov x0, #1000
        mov x8, #54
        svc #0

        // set group ID - setgid
        mov x0, #1000
        mov x8, #55
        svc #0

        // exit with status 1
        mov x0, #1
        mov x8, #93
        svc #0
