"""
抢票辅助脚本 - 模拟人类操作行为
用途：辅助点击和鼠标移动，其余操作由人工完成
"""

import time
import random
import math
import pyautogui
import numpy as np
from dataclasses import dataclass
from typing import Tuple, List, Optional


# ============================================================
# 1. 人类行为模拟器
# ============================================================

@dataclass
class HumanBehaviorConfig:
    """人类行为参数配置"""
    # 鼠标移动
    min_move_duration: float = 0.3
    max_move_duration: float = 1.2
    curve_noise: float = 0.15          # 贝塞尔曲线噪声
    overshoot_probability: float = 0.3  # 过冲概率
    overshoot_distance: int = 15        # 过冲距离

    # 点击
    min_click_delay: float = 0.05
    max_click_delay: float = 0.15       # 按下和释放之间
    double_click_interval: float = 0.12

    # 等待
    min_think_time: float = 0.2
    max_think_time: float = 0.8

    # 微小抖动
    jitter_range: int = 3               # 目标位置随机偏移像素


class BezierCurve:
    """贝塞尔曲线生成器 - 模拟人类鼠标轨迹"""

    @staticmethod
    def generate_control_points(
        start: Tuple[int, int],
        end: Tuple[int, int],
        num_controls: int = 2,
        noise: float = 0.15
    ) -> List[Tuple[float, float]]:
        """生成带随机偏移的控制点"""
        points = [start]
        dx = end[0] - start[0]
        dy = end[1] - start[1]
        distance = math.sqrt(dx**2 + dy**2)

        for i in range(1, num_controls + 1):
            t = i / (num_controls + 1)
            # 基础插值点
            bx = start[0] + dx * t
            by = start[1] + dy * t
            # 添加垂直于移动方向的随机偏移
            offset = distance * noise * random.uniform(-1, 1)
            angle = math.atan2(dy, dx) + math.pi / 2
            bx += offset * math.cos(angle)
            by += offset * math.sin(angle)
            points.append((bx, by))

        points.append(end)
        return points

    @staticmethod
    def interpolate(
        control_points: List[Tuple[float, float]],
        num_steps: int
    ) -> List[Tuple[int, int]]:
        """De Casteljau 算法插值贝塞尔曲线"""
        path = []
        for step in range(num_steps + 1):
            t = step / num_steps
            # 应用非线性时间（模拟加速-减速）
            t = BezierCurve._ease_in_out(t)
            points = list(control_points)
            while len(points) > 1:
                new_points = []
                for i in range(len(points) - 1):
                    x = points[i][0] + (points[i+1][0] - points[i][0]) * t
                    y = points[i][1] + (points[i+1][1] - points[i][1]) * t
                    new_points.append((x, y))
                points = new_points
            path.append((int(points[0][0]), int(points[0][1])))
        return path

    @staticmethod
    def _ease_in_out(t: float) -> float:
        """缓入缓出函数 - 模拟人类移动加速度"""
        if t < 0.5:
            return 2 * t * t
        else:
            return -1 + (4 - 2 * t) * t


class HumanMouseSimulator:
    """人类鼠标行为模拟器"""

    def __init__(self, config: Optional[HumanBehaviorConfig] = None):
        self.config = config or HumanBehaviorConfig()
        pyautogui.FAILSAFE = True  # 鼠标移到左上角紧急停止
        pyautogui.PAUSE = 0        # 禁用 pyautogui 内置延迟

    def move_to(self, x: int, y: int) -> Tuple[int, int]:
        """
        以人类方式移动鼠标到目标位置
        返回实际到达的位置
        """
        # 添加目标位置抖动
        jitter = self.config.jitter_range
        target_x = x + random.randint(-jitter, jitter)
        target_y = y + random.randint(-jitter, jitter)

        start = pyautogui.position()
        start_pos = (start.x, start.y)
        end_pos = (target_x, target_y)

        # 计算距离决定步数和时间
        distance = math.sqrt(
            (end_pos[0] - start_pos[0])**2 +
            (end_pos[1] - start_pos[1])**2
        )

        # 距离越远，时间越长（但不是线性的）
        duration = self.config.min_move_duration + \
            (self.config.max_move_duration - self.config.min_move_duration) * \
            min(distance / 1000, 1.0)
        duration *= random.uniform(0.8, 1.2)  # 随机波动

        # 步数：距离越远步数越多
        num_steps = max(int(distance / 3), 20)

        # 生成贝塞尔曲线路径
        num_controls = 2 if distance > 200 else 1
        control_points = BezierCurve.generate_control_points(
            start_pos, end_pos,
            num_controls=num_controls,
            noise=self.config.curve_noise
        )
        path = BezierCurve.interpolate(control_points, num_steps)

        # 添加微小抖动到路径点
        path = self._add_micro_jitter(path)

        # 执行移动
        step_delay = duration / len(path)
        for point in path:
            pyautogui.moveTo(point[0], point[1], _pause=False)
            # 非均匀延迟
            actual_delay = step_delay * random.uniform(0.5, 1.5)
            time.sleep(actual_delay)

        # 模拟过冲（overshoot）
        if random.random() < self.config.overshoot_probability and distance > 50:
            self._simulate_overshoot(end_pos)

        final_pos = pyautogui.position()
        return (final_pos.x, final_pos.y)

    def click_at(self, x: int, y: int, button: str = 'left') -> None:
        """人类方式点击：先移动，然后按下-等待-释放"""
        # 移动到目标
        self.move_to(x, y)

        # 随机短暂停顿（人类反应时间）
        think_time = random.uniform(
            self.config.min_think_time,
            self.config.max_think_time
        )
        time.sleep(think_time)

        # 按下-持续-释放（而非瞬间click）
        hold_time = random.uniform(
            self.config.min_click_delay,
            self.config.max_click_delay
        )
        pyautogui.mouseDown(button=button, _pause=False)
        time.sleep(hold_time)
        pyautogui.mouseUp(button=button, _pause=False)

    def click_sequence(self, positions: List[Tuple[int, int]]) -> None:
        """
        依次点击多个位置
        每次点击之间有随机延迟
        """
        for i, (x, y) in enumerate(positions):
            self.click_at(x, y)
            if i < len(positions) - 1:
                # 操作间随机等待
                wait = random.uniform(0.3, 1.5)
                time.sleep(wait)

    def _simulate_overshoot(self, target: Tuple[int, int]) -> None:
        """模拟鼠标过冲然后修正"""
        overshoot_dist = self.config.overshoot_distance
        angle = random.uniform(0, 2 * math.pi)
        overshoot_x = int(target[0] + overshoot_dist * math.cos(angle))
        overshoot_y = int(target[1] + overshoot_dist * math.sin(angle))

        # 快速过冲
        pyautogui.moveTo(overshoot_x, overshoot_y, duration=0.05, _pause=False)
        time.sleep(random.uniform(0.05, 0.15))

        # 修正回目标
        jitter = 2
        final_x = target[0] + random.randint(-jitter, jitter)
        final_y = target[1] + random.randint(-jitter, jitter)
        pyautogui.moveTo(final_x, final_y, duration=0.1, _pause=False)

    def _add_micro_jitter(
        self, path: List[Tuple[int, int]]
    ) -> List[Tuple[int, int]]:
        """给路径添加微小随机抖动"""
        jittered = []
        for i, (x, y) in enumerate(path):
            # 首尾不抖动
            if i == 0 or i == len(path) - 1:
                jittered.append((x, y))
            else:
                jx = x + random.randint(-1, 1)
                jy = y + random.randint(-1, 1)
                jittered.append((jx, jy))
        return jittered


# ============================================================
# 2. 抢票操作编排器
# ============================================================

class TicketGrabber:
    """
    抢票辅助器
    只负责 点击->移动->点击 这个核心动作
    其余操作（登录、选座、支付）由人工完成
    """

    def __init__(self):
        self.mouse = HumanMouseSimulator()
        self._positions = {}

    def calibrate(self) -> None:
        """
        校准模式：让用户手动指定关键位置
        """
        print("=" * 50)
        print("  抢票脚本 - 位置校准")
        print("=" * 50)
        print()

        positions_to_mark = [
            ("first_click", "第一次点击位置（如：抢票按钮）"),
            ("second_click", "第二次点击位置（如：确认按钮）"),
        ]

        for key, description in positions_to_mark:
            input(f"请将鼠标移到 [{description}]，然后按 Enter...")
            pos = pyautogui.position()
            self._positions[key] = (pos.x, pos.y)
            print(f"  ✓ 已记录: ({pos.x}, {pos.y})")
            print()

        print("校准完成！记录的位置：")
        for key, pos in self._positions.items():
            print(f"  {key}: {pos}")
        print()

    def set_positions(
        self,
        first_click: Tuple[int, int],
        second_click: Tuple[int, int]
    ) -> None:
        """直接设置点击位置（跳过校准）"""
        self._positions["first_click"] = first_click
        self._positions["second_click"] = second_click

    def execute(self, pre_delay: float = 0) -> None:
        """
        执行核心操作：点击 -> 移动 -> 点击
        
        Args:
            pre_delay: 执行前等待秒数（留时间切换窗口）
        """
        if "first_click" not in self._positions:
            raise RuntimeError("请先校准位置或调用 set_positions()")

        first = self._positions["first_click"]
        second = self._positions["second_click"]

        if pre_delay > 0:
            print(f"将在 {pre_delay} 秒后执行，请切换到目标窗口...")
            for i in range(int(pre_delay), 0, -1):
                print(f"  {i}...")
                time.sleep(1)

        print("▶ 开始执行")

        # 第一次点击
        print(f"  → 点击位置1: {first}")
        self.mouse.click_at(first[0], first[1])

        # 操作间随机等待
        gap = random.uniform(0.5, 1.2)
        print(f"  ⏱ 等待 {gap:.2f}s")
        time.sleep(gap)

        # 第二次点击
        print(f"  → 点击位置2: {second}")
        self.mouse.click_at(second[0], second[1])

        print("✓ 执行完成")

    def execute_at_time(
        self,
        target_hour: int,
        target_minute: int,
        target_second: int = 0
    ) -> None:
        """
        定时执行 - 在指定时间点执行操作
        """
        import datetime

        now = datetime.datetime.now()
        target = now.replace(
            hour=target_hour,
            minute=target_minute,
            second=target_second,
            microsecond=0
        )
        if target <= now:
            target += datetime.timedelta(days=1)

        wait_seconds = (target - now).total_seconds()
        print(f"定时任务：将在 {target.strftime('%H:%M:%S')} 执行")
        print(f"距离执行还有 {wait_seconds:.1f} 秒")
        print("（脚本运行中，请不要关闭）")
        print()

        # 提前2秒进入精确等待
        if wait_seconds > 2:
            time.sleep(wait_seconds - 2)

        # 精确等待（忙等）
        while datetime.datetime.now() < target:
            time.sleep(0.001)

        # 执行
        self.execute()


# ============================================================
# 3. 高级功能：多次重试
# ============================================================

class RetryGrabber(TicketGrabber):
    """带重试机制的抢票器"""

    def execute_with_retry(
        self,
        max_retries: int = 5,
        retry_interval: float = 1.0,
        pre_delay: float = 3
    ) -> None:
        """
        多次尝试抢票
        
        Args:
            max_retries: 最大重试次数
            retry_interval: 重试间隔（秒）
            pre_delay: 首次执行前等待
        """
        if pre_delay > 0:
            print(f"将在 {pre_delay} 秒后开始，请切换到目标窗口...")
            for i in range(int(pre_delay), 0, -1):
                print(f"  {i}...")
                time.sleep(1)

        for attempt in range(1, max_retries + 1):
            print(f"\n{'='*30}")
            print(f"  第 {attempt}/{max_retries} 次尝试")
            print(f"{'='*30}")

            try:
                self.execute()
            except Exception as e:
                print(f"  ✗ 出错: {e}")

            if attempt < max_retries:
                wait = retry_interval * random.uniform(0.8, 1.3)
                print(f"  等待 {wait:.2f}s 后重试...")
                time.sleep(wait)

        print("\n所有尝试已完成")


# ============================================================
# 4. 使用示例
# ============================================================

def main():
    """主函数 - 使用示例"""
    print("╔══════════════════════════════════════╗")
    print("║       抢票辅助脚本 v1.0              ║")
    print("║  操作：点击 → 移动 → 点击            ║")
    print("║  其余操作请手动完成                   ║")
    print("╚══════════════════════════════════════╝")
    print()

    grabber = RetryGrabber()

    print("请选择模式：")
    print("  1. 交互式校准 + 立即执行")
    print("  2. 交互式校准 + 定时执行")
    print("  3. 直接指定坐标执行")
    print("  4. 获取当前鼠标位置（辅助工具）")
    print()

    choice = input("选择 (1/2/3/4): ").strip()

    if choice == "4":
        # 辅助工具：持续显示鼠标位置
        print("持续显示鼠标位置（Ctrl+C 退出）:")
        try:
            while True:
                pos = pyautogui.position()
                print(f"\r  鼠标位置: ({pos.x}, {pos.y})    ", end="")
                time.sleep(0.1)
        except KeyboardInterrupt:
            print("\n退出")
        return

    if choice in ("1", "2"):
        grabber.calibrate()
    elif choice == "3":
        x1 = int(input("第一个点击位置 X: "))
        y1 = int(input("第一个点击位置 Y: "))
        x2 = int(input("第二个点击位置 X: "))
        y2 = int(input("第二个点击位置 Y: "))
        grabber.set_positions((x1, y1), (x2, y2))
    else:
        print("无效选择")
        return

    if choice == "2":
        hour = int(input("执行时间 - 小时 (0-23): "))
        minute = int(input("执行时间 - 分钟 (0-59): "))
        second = int(input("执行时间 - 秒 (0-59): "))
        grabber.execute_at_time(hour, minute, second)
    else:
        retry = input("是否启用重试模式? (y/n): ").strip().lower()
        if retry == 'y':
            retries = int(input("重试次数: ") or "3")
            grabber.execute_with_retry(
                max_retries=retries,
                pre_delay=3
            )
        else:
            grabber.execute(pre_delay=3)


if __name__ == "__main__":
    main()