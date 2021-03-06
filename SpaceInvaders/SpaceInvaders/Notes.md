#  Learning Notes


## Terms

- buffer:
    A portion of the RAM used to hold a temporary image. OpenGL uses a double buffering scheme, where the front one displays an image and the back one is used for drawing. The buffers can be swapped.


## Libraries

- GLFW:
    For cross-platform windows.
    
- GLEW:
    To handle the loading of the OpenGL functions.



## Functions

- `fprintf`:
    Writes a C string to an output stream. For printing errors, it is used the `stderr` stream.
    
- `glfwSwapBuffers`:
    Swaps the front and back buffers.
    
    
## Operators

### Bitwise
- `variable << n`:
    Shifts the bits of `variable` by `n` times to the left.
    
- `a | b`:
    Logical  `OR` with the bits of `a` and `b`.
    
    
## Types

- `size_t`:
    Alias of unsigned integer, able to represent the size of any object in bytes.
    
    
## References
- nicktasios.nl
- cplusplus.com
- cprogramming.com
