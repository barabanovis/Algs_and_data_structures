#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Скрипт для построения графика зависимости вероятности 0 столкновений 
от ёмкости таблицы с вертикальными линиями и подписями абсцисс.
Данные: results/probability.csv
"""

import pandas as pd
import matplotlib.pyplot as plt
from pathlib import Path


def plot_probability_vs_capacity(
    csv_path: str = "results/probability.csv",
    output_path: str = "results/probability_plot.png"
):
    """Читает CSV и строит график с вертикальными линиями и подписями."""

    # Загрузка данных
    df = pd.read_csv(csv_path)

    # Проверка колонок
    required_cols = ['table_capacity', 'probability[at least 1 collision]']
    if not all(col in df.columns for col in required_cols):
        raise ValueError(f"Файл должен содержать колонки: {required_cols}")

    # Настройка графика
    fig, ax = plt.subplots(figsize=(12, 7))
    plt.style.use('seaborn-v0_8-darkgrid')

    # 🔹 Вертикальные линии от каждой точки до оси X
    for _, row in df.iterrows():
        ax.plot(
            [row['table_capacity'], row['table_capacity']],  # x1, x2
            [0, row['probability[at least 1 collision]']],            # y1, y2
            color='#95A5A6',
            linestyle=':',
            linewidth=1,
            alpha=0.6,
            zorder=1
        )

    # 🔹 Подписи значений table_capacity под осью X
    for _, row in df.iterrows():
        ax.text(
            row['table_capacity'],
            -0.03,  # чуть ниже оси X
            str(int(row['table_capacity'])),
            ha='center',
            va='top',
            fontsize=9,
            fontweight='bold',
            color='#2C3E50',
            bbox=dict(boxstyle='round,pad=0.2', facecolor='#ECF0F1',
                      edgecolor='#BDC3C7', alpha=0.7)
        )

    # Основная кривая данных
    ax.plot(
        df['table_capacity'],
        df['probability[at least 1 collision]'],
        marker='o',
        linestyle='-',
        linewidth=2.5,
        markersize=10,
        color='#2E86AB',
        markerfacecolor='#E94F37',
        markeredgecolor='white',
        markeredgewidth=2.5,
        label='P(0 collisions)',
        zorder=4
    )

    # 🔹 Горизонтальная линия y = 50%
    ax.axhline(
        y=0.5,
        color='#27AE60',
        linestyle='--',
        linewidth=2,
        label='Порог 50%',
        zorder=2
    )

    # Подпись к линии 50%
    ax.text(
        df['table_capacity'].max() * 0.55,
        0.525,
        '50%',
        color='#27AE60',
        fontsize=11,
        fontweight='bold',
        bbox=dict(boxstyle='round,pad=0.3', facecolor='white',
                  edgecolor='#27AE60', alpha=0.9),
        zorder=3
    )

    # Подписи осей и заголовок
    ax.set_xlabel('Ёмкость таблицы', fontsize=12, fontweight='bold')
    ax.set_ylabel('Вероятность хотя бы одной коллизии',
                  fontsize=12, fontweight='bold')
    ax.set_title('Зависимость P(0 collisions) от размера таблицы',
                 fontsize=14, fontweight='bold', pad=20)

    # Форматирование оси Y в процентах
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda y, _: f'{y:.0%}'))

    # Настройка оси X: скрываем стандартные подписи, т.к. есть кастомные
    ax.set_xticks([])

    # Ограничения осей с отступом снизу для подписей
    y_max = df['probability[at least 1 collision]'].max()
    ax.set_ylim(-0.12, y_max * 1.05)  # отступ снизу для подписей абсцисс
    ax.set_xlim(df['table_capacity'].min() - 15,
                df['table_capacity'].max() + 15)

    # Сетка и легенда
    ax.grid(True, alpha=0.3, linestyle='--', axis='y', zorder=0)
    ax.legend(fontsize=10, frameon=True, shadow=False, loc='upper right')

    # Убираем лишние отступы и сохраняем
    plt.tight_layout()
    Path(output_path).parent.mkdir(parents=True, exist_ok=True)
    plt.savefig(output_path, dpi=300, bbox_inches='tight')
    print(f"✅ График сохранён: {output_path}")

    plt.show()

    # 🔍 Анализ пересечения с 50%
    above_50 = df[df['probability[at least 1 collision]'] >= 0.5]
    below_50 = df[df['probability[at least 1 collision]'] < 0.5]

    if not above_50.empty and not below_50.empty:
        last_above = above_50.iloc[-1]
        first_below = below_50.iloc[0]
        print(f"\n🎯 Пересечение порога 50%:")
        print(
            f"   • capacity={int(last_above['table_capacity'])}: P={last_above['probability[at least 1 collision]']:.1%} (≥50%)")
        print(
            f"   • capacity={int(first_below['table_capacity'])}: P={first_below['probability[at least 1 collision]']:.1%} (<50%)")
        print(
            f"   → Критическая ёмкость ≈ {int(last_above['table_capacity'])}–{int(first_below['table_capacity'])}")

    # Статистика
    print(
        f"\n📊 Данные: {len(df)} точек, capacity {df['table_capacity'].min()}–{df['table_capacity'].max()}")


if __name__ == "__main__":
    plot_probability_vs_capacity()
