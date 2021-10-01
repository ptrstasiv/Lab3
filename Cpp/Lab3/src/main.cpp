#include <iostream>

//Константа яка задає початкове значення для табуляції функції
constexpr float IntialFunctionStep = 0.0f;

constexpr int IterationsLimit = 1024;

inline float GetFunctionResult(const float root)
{
	return root * root * root - 4.0f * root;
}

inline std::pair<float, float> FindFunctionInterval(const float stepSize)
{
	const float a = IntialFunctionStep;
	const float instFunctionV = GetFunctionResult(a);

	float step = a;

	for(int i = 0; i <= IterationsLimit; ++i)
	{
		if (GetFunctionResult(step) * instFunctionV < 0)
			return { a, step };

		step += stepSize;
	}
}

int main()
{
	std::cout << "Equation is x^3 - 4x\n\n";

	while (1)
	{
		std::cout << "\nEnter result value tolerance: ";

		float tolerance = 1e-1f;
		std::cin >> tolerance;


		std::cout << "\nEnter interval: ";

		float a = 0.0f;
		float b = 0.0f;
		std::cin >> a >> b;

		//Перевірка чи в заданому інтервалі існують корені
		if (GetFunctionResult(a) * GetFunctionResult(b) > 0.0f)
		{
			//Якщо інтервал є недійсним інтервал буде визначений методом табулювання функції
			auto interval = FindFunctionInterval(1.0f);
			a = interval.first;
			b = interval.second;

			if (GetFunctionResult(a) * GetFunctionResult(b) > 0.0f)
			{
				std::cout << "\nOn this interval there isn't any root or tolerance value is too small!\n\n";

				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				continue;
			}
		}


		//Перевірка чи коренем може бути одне з чисел яке задає інтервал
		if (std::abs(GetFunctionResult(a)) <= tolerance)
		{
			std::cout << "\nRoot is: " << a << "\n\n";
			continue;
		}
		else if (std::abs(GetFunctionResult(b)) <= tolerance)
		{
			std::cout << "\nRoot is: " << b << "\n\n";
			continue;
		}


		float c = 0.0f;
		int iterationsCount = 0;

		while (1)
		{
			c = (a + b) / 2.0f;

			if (std::abs(GetFunctionResult(c)) <= tolerance
				|| iterationsCount >= IterationsLimit)
			{
				std::cout << "\nRoot is: " << c << "\nComputed in: " << iterationsCount << " iterations";
				break;
			}

			if (GetFunctionResult(a) * GetFunctionResult(c) < 0.0f)
				b = c;
			else
				a = c;

			iterationsCount++;
		}

		std::cout << "\n\n";
	}

	return(0);
}