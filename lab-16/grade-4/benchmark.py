#!/usr/bin/env python3
"""
benchmark.py — гоняет ex9_benchmark на разных N × threads,
собирает данные в benchmark.csv и строит график benchmark.png.

Запуск:
    make ex9_benchmark   # должен быть собран
    python3 benchmark.py
"""
import os
import subprocess
import csv
from pathlib import Path

import matplotlib
matplotlib.use("Agg")  # без X11
import matplotlib.pyplot as plt

HERE = Path(__file__).resolve().parent
EX9 = HERE / "ex9_benchmark"
CSV = HERE / "benchmark.csv"
PNG = HERE / "benchmark.png"

# Размеры и числа потоков — подобраны так, чтобы вся таблица считалась за пару минут.
SIZES   = [128, 256, 384, 512, 640, 768]
THREADS = [1, 2, 4, 8, 16]


def run(N: int, T: int) -> float:
    """Запускает ex9 и возвращает время в миллисекундах."""
    out = subprocess.check_output([str(EX9), str(N), str(T)]).decode().strip()
    # формат: "N,threads,time_ms"
    return float(out.split(",")[2])


def main() -> None:
    if not EX9.exists():
        raise SystemExit(f"Сначала собери: cd {HERE} && make")

    rows = []
    for N in SIZES:
        for T in THREADS:
            ms = run(N, T)
            print(f"N={N:5d}  threads={T:3d}  {ms:8.2f} ms")
            rows.append((N, T, ms))

    with CSV.open("w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["N", "threads", "time_ms"])
        w.writerows(rows)

    fig, ax = plt.subplots(figsize=(8, 5))
    for T in THREADS:
        xs = [N for (N, t, _) in rows if t == T]
        ys = [ms for (_, t, ms) in rows if t == T]
        ax.plot(xs, ys, marker="o", label=f"{T} thread(s)")
    ax.set_title("Matrix multiplication N×N — time vs threads")
    ax.set_xlabel("Matrix size N")
    ax.set_ylabel("Time, ms")
    ax.set_yscale("log")
    ax.grid(True, which="both", linestyle="--", alpha=0.5)
    ax.legend()
    fig.tight_layout()
    fig.savefig(PNG, dpi=110)
    print(f"\nSaved {CSV}\nSaved {PNG}")


if __name__ == "__main__":
    main()
