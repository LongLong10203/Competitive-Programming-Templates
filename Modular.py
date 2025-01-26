class Modular:
    _MOD = int(1e9 + 7)  # Default modulus

    @staticmethod
    def set_mod(mod):
        assert mod > 0, "Modulus must be a positive integer"
        Modular._MOD = mod

    def __init__(self, value):
        self.value = value % Modular._MOD if value >= 0 else (value % Modular._MOD + Modular._MOD) % Modular._MOD

    def __int__(self):
        return self.value

    def __repr__(self):
        return str(self.value)

    def __eq__(self, other):
        if isinstance(other, Modular):
            return self.value == other.value
        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __lt__(self, other):
        if isinstance(other, Modular):
            return self.value < other.value
        return NotImplemented

    def __add__(self, other):
        if isinstance(other, Modular):
            return Modular(self.value + other.value)
        return Modular(self.value + other)

    def __sub__(self, other):
        if isinstance(other, Modular):
            return Modular(self.value - other.value)
        return Modular(self.value - other)

    def __mul__(self, other):
        if isinstance(other, Modular):
            return Modular(self.value * other.value)
        return Modular(self.value * other)

    def __truediv__(self, other):
        if isinstance(other, Modular):
            return self * other.inv()
        return self * Modular(other).inv()

    def __neg__(self):
        return Modular(-self.value)

    def __pow__(self, power):
        assert power >= 0, "Power must be non-negative"
        return Modular(pow(self.value, power, Modular._MOD))

    def inv(self):
        assert self.value != 0, "Inverse does not exist for zero"
        return self ** (Modular._MOD - 2)

def main() -> None:
    ...

if __name__ == "__main__":
    main()