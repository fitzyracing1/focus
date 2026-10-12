# focus

focus is a header-only C++ interface for AI models (`ai-iface.hpp`, namespace `ai`). A single abstract `ai::Model` works for any backend: local, remote API or mock. Web and internet concerns are deliberately kept out.

## API (from the header)

- `virtual std::string infer(const std::string& prompt, const std::string& system = "") = 0;`
- `virtual void infer_stream(...)` for streaming generation
- `virtual std::vector<float> embed(const std::string& text)`
- `virtual std::string name() const` (default `"unnamed"`), `virtual bool is_ready() const` (default `true`)
- `class MockModel : public Model` for testing

## Getting started

Copy `ai-iface.hpp` into your include path and add `#include "ai-iface.hpp"`. Then subclass `ai::Model` and implement `infer`. It needs only the standard library headers `<string>`, `<vector>`, `<memory>` and `<functional>`.

`index.html` is the project page. The repo had no README before this docs commit, and it has no tests and no LICENSE file.

Copyright (c) 2026 Joshua Almeida

## Documentation

- In-repo docs: [docs/](docs/index.md)
- Wiki: [https://github.com/fitzyracing1/focus/wiki](https://github.com/fitzyracing1/focus/wiki)
