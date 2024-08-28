# <h1 align="center">🧠 Cache Simulation and LRU Stack Project</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C Language"/>
  <img src="https://img.shields.io/badge/OS-Operating_System-2c3e50" alt="Operating Systems"/>
  <img src="https://img.shields.io/badge/Simulation-Cache-FF5733" alt="Cache Simulation"/>
</p>

<p align="center">
  A project focused on simulating cache memory behavior and implementing an LRU (Least Recently Used) stack for efficient cache management.
</p>

---

## 🌟 **Features**
- **📦 Cache Simulation**: Models the behavior of a CPU cache, allowing detailed analysis of cache hits, misses, and overall performance.
- **🔄 LRU Stack Implementation**: Manages cache entries using the LRU (Least Recently Used) replacement policy.
- **🧪 Unit Testing**: Includes unit tests to verify the correctness and performance of the cache simulation and LRU stack.
- **⚙️ Modular Design**: Separates concerns between cache simulation, LRU stack management, and testing, enabling easy extension and maintenance.

---

## 🛠 **Tech Stack**
- **Programming Language**: <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white"/> C
- **Environment**: Linux-based development and testing.
- **Build System**: Makefile for easy compilation and execution.

---

## 🗂 **Project Structure**
1. **Cache Simulation**:
   - `cachesim.c` & `cachesim.h`: Core modules for simulating cache behavior, including cache access patterns, hit/miss tracking, and overall performance metrics.
   - `cachesim`: Binary executable for running the cache simulation.
   - `cachetest`: Test suite for verifying the functionality of the cache simulation.
2. **LRU Stack Implementation**:
   - `lrustack.c` & `lrustack.h`: Implements the LRU (Least Recently Used) stack mechanism for cache management.
   - `lrustacktest.c`: Contains unit tests to ensure the LRU stack operates correctly.
   - `lrustacktest`: Binary executable for running the LRU stack tests.
3. **Testing**:
   - `cachetest`: Executable for testing the cache simulation.
   - `lrustacktest`: Executable for testing the LRU stack implementation.

---

## 🚀 **Getting Started**

### Prerequisites
- GCC Compiler (or any C compiler)
- Linux environment (for development and testing)

### Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/Cache-LRU-Simulation.git

# Cachsim-Model-(ECE3058 Project 3)
Made a cache sim model in VScode using C++ as a coding language
