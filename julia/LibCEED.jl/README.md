# LibCEED.jl: Julia Interface for [libCEED](https://github.com/CEED/libCEED)

Please see the [LibCEED.jl
documentation](http://ceed.exascaleproject.org/libCEED-julia-docs/dev/) for
usage and API documentation.

## Installation

The LibCEED.jl package can be installed with Julia's package manager by running
`] add LibCEED`. This will automatically install a pre-built binary of the
libCEED library. If you require features of a specific build of libCEED (e.g.
CUDA/GPU support, specific compiler flags, etc.) then you should compile your
own version of the libCEED library, and configure LibCEED.jl to use this binary
as described in the [Configuring LibCEED.jl](@ref) section.

**Warning:** the pre-built libCEED binaries do not support CUDA backends

The pre-built binaries automatically installed by LibCEED.jl (through the
[libCEED_jll](https://juliahub.com/ui/Packages/libCEED_jll/LB2fn) package) are
not built with CUDA support. If you want to run libCEED on the GPU, you will
have to build libCEED from source and configure LibCEED.jl as described in the
[Configuring LibCEED.jl](@ref) section.

### Configuring LibCEED.jl

By default, LibCEED.jl will use the pre-built libCEED binaries provided by the
[libCEED_jll](https://juliahub.com/ui/Packages/libCEED_jll/LB2fn) package. If
you wish to use a different libCEED binary (e.g. one built from source), this
can be achieved using `Overrides.toml`. Edit (or create, if it does not exist)
the file `~/.julia/artifacts/Overrides.toml`, and add the following section:

```toml
[762fde13-7596-547b-826d-8223c52d51c1]
libCEED = "/absolute/path/to/libCEED"
```

In the above, `762fde13-7596-547b-826d-8223c52d51c1` is the UUID of the
libCEED_jll package (it can be copied verbatim), and `/absolute/path/to/libCEED`
is a path to the directory enclosing the `lib` directory containing the libCEED
dynamic library. In other words, the dynamic library `libceed.so` or
`libceed.dylib` (depending on the platform) should be found within the directory
`/absolute/path/to/libCEED/lib`.

More information about `Overrides.toml` is available in the [Pkg
documentation](https://pkgdocs.julialang.org/v1/artifacts/#Overriding-artifact-locations)
and the [BinaryBuilder
documentation](https://docs.binarybuilder.org/stable/jll/#Overriding-the-artifacts-in-JLL-packages).
