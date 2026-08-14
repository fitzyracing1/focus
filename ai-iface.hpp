// ai-iface.hpp
// Minimal, uniform C++ AI Model interface (header-only)
//
// One abstract Model works for any backend: local, remote API, mock, etc.
// Intentionally keeps the internet / web concerns out of this core header.
//
// Note: bare "ai.h" is already used by several libraries.
// This .hpp + namespace version is safer.

#ifndef AI_IFACE_HPP
#define AI_IFACE_HPP

#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace ai {

/**
 * Abstract base for any inference backend.
 */
class Model {
public:
    virtual ~Model() = default;

    // Synchronous generation / query
    virtual std::string infer(const std::string& prompt,
                              const std::string& system = "") = 0;

    // Optional streaming
    virtual void infer_stream(const std::string& prompt,
                              std::function<void(const std::string&)> on_token,
                              const std::string& system = "") {
        on_token(infer(prompt, system));
    }

    // Embedding (optional)
    virtual std::vector<float> embed(const std::string& text) {
        return {};
    }

    virtual std::string name() const { return "unnamed"; }
    virtual bool is_ready() const { return true; }
};

// ---------------------------------------------------------------------------
// Built-in mock (zero dependencies, always available)
// ---------------------------------------------------------------------------
class MockModel : public Model {
public:
    std::string infer(const std::string& prompt,
                      const std::string& system = "") override {
        return "[mock] " + (system.empty() ? prompt : system + " | " + prompt);
    }
    std::string name() const override { return "mock"; }
};

/**
 * Factory
 *
 *   auto m = ai::create();          // mock
 *   auto m = ai::create("mock");
 */
inline std::unique_ptr<Model> create(const std::string& backend = "mock") {
    if (backend.empty() || backend == "mock") {
        return std::make_unique<MockModel>();
    }
    // Unknown → still return a usable mock so code never crashes on create()
    return std::make_unique<MockModel>();
}

} // namespace ai

#endif // AI_IFACE_HPP
