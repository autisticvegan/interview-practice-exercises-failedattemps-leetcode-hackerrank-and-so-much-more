constexpr int fib(const int i)
{
	const auto sqrt_5 = std::sqrt(5);

	if (i == 0) return 0;
	if (i == 1) return 1;

	return static_cast<int>(std::round((std::pow(1 + sqrt_5, i) - std::pow(1 - sqrt_5, i)) / (std::pow(2, i) * sqrt_5)));
}
