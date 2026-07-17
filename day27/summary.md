# Day 27 — AI-Powered Python-to-C++ Code Conversion

Today, I explored how LLMs can be used to convert slow Python programs into high-performance C++ implementations.

I began by setting up a small **AI code-generation pipeline** that:

1. Accepts Python code as input.
2. Sends it to an LLM with instructions to generate optimized C++.
3. Writes the generated response into `main.cpp`.
4. Compiles the file using `clang++`.
5. Executes the compiled program using Python’s `subprocess` module.
6. Compares the C++ execution time with the original Python version.

I connected to two OpenAI-compatible APIs:

* A local Ollama server
* OpenRouter for accessing hosted models

I also retrieved information about my computer, including the operating system, CPU architecture and available compilers. This helped construct a prompt that gave the model information about the environment where the generated C++ code would be compiled.

The test program approximated the value of π by performing **200 million loop iterations**.

The original Python implementation produced:

* Result: `3.141592656089`
* Execution time: approximately `31.99 seconds`

Initially, I used `gpt-oss:latest` to generate the C++ conversion. Although its generated code worked well in my instructor’s environment, it used:

```cpp
#include <bits/stdc++.h>
```

This is a non-standard GCC-specific header and was not supported by my Windows Clang setup.

While debugging this, I learned that:

* Installing the LLVM compiler does not automatically guarantee compatibility with every C++ header.
* `bits/stdc++.h` is commonly available with GCC but is not part of standard C++.
* Portable C++ programs should include only the headers they actually use, such as `<iostream>`, `<chrono>`, `<iomanip>` and `<cstdint>`.
* `subprocess.run(..., check=True)` raises a `CalledProcessError` whenever compilation or execution fails.
* When `capture_output=True` is used, the actual compiler error is stored in `stderr` and must be printed manually.

I improved my `compile_and_run()` function so that it now clearly displays compiler errors instead of only showing a generic Python traceback.

Rather than installing and configuring another C++ toolchain, I switched the code-generation model to:

```text
tencent/hy3:free
```

The Tencent model generated C++ code that compiled successfully on my existing setup and produced the same result as the Python program.

Its execution time was approximately:

```text
1.157 seconds
```

Compared with the Python execution time of `31.99 seconds`, the generated C++ program was approximately:

```text
27.64× faster
```

## Key takeaways

* LLMs can be used as practical code-transpilation and optimization tools.
* Generated code must still be tested for compatibility with the target operating system and compiler.
* A model that performs well in one environment may generate code that fails in another.
* Faster execution is only useful when the optimized program still produces the correct result.
* Proper error handling is important when automating compilation through Python.
* Different LLMs can produce significantly different code quality, portability and performance.

Today’s experiment showed that AI-generated code can provide major performance improvements, but selecting the right model and validating its output are just as important as generating the code itself.
