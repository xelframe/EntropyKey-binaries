# Binaries in releases

# EntropyKey

A tiny C utility to generate random secure passwords right from your terminal, powered by CPU clock entropy.

## 🚀 Features

- Generates strong passwords with letters, numbers, symbols and custom characters
- Uses CPU timestamp counter (`rdtsc`) for seeding randomness
- Super lightweight, fast and dependency-free
- Command-line options to customize everything

## 🛠️ Build

Just run:

```bash
make
```

No dependencies, just pure C.

## 🧪 Usage

```bash
./entropykey [options]
```

### Available options:

```
  -l <length>    Passphrase length (default: 16)
  -c <count>     Passphrase count (default: 1)
  -C <chars>     Additional characters
  -a             Add alphabet characters (default true, can be disabled with -a)
  -n             Add number characters (default true, can be disabled with -n)
  -s             Add special characters (default false)
```

### Example:

```bash
./entropykey -l 24 -c 5 -s -C "_-+="
```

Generates 5 passwords, each 24 characters long, with special characters and some custom symbols.

## 🔒 Entropy source

This tool uses the CPU’s **timestamp counter (`rdtsc`)** to seed the random number generator, ensuring high variability and decent randomness without relying on external libraries or `/dev/urandom`.

## 📜 License

Released under the **GNU GPL v3.0**.
See [LICENSE](LICENSE) for full details.

---

Made with ❤️ by [honakac](https://github.com/honakac)
