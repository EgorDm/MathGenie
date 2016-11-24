#pragma once
namespace MathLab
{
	struct BaseOP
	{
		virtual ~BaseOP()
		{
		}

		BaseOP()
		{
		}

		virtual double execute()
		{
			return 0;
		}
	};

	struct OperatorValue : BaseOP
	{
		double value;

		explicit OperatorValue(double value)
			: value(value)
		{
		}


		double execute() override {
			return value;
		};
	};

	struct Operator : BaseOP
	{
		virtual ~Operator()
		{
			delete(left);
			delete(right);
		}

		BaseOP* left;
		BaseOP* right;
		int precedence = 0;

		explicit Operator(BaseOP* left)
			: left(left), right(nullptr)
		{
		}

		virtual double calc()
		{
			return left->execute();
		}

		virtual double execute() override
		{
			if (right == nullptr)
			{
				if (left == nullptr)
				{
					return 0;
				}
				return left->execute();
			}
			return calc();
		}

		BaseOP* getLeft() const
		{
			return left;
		}

		BaseOP* getRight() const
		{
			return right;
		}


		void setLeft(BaseOP* operator_)
		{
			left = operator_;
		}

		void setRight(BaseOP* operator_)
		{
			right = operator_;
		}


		int getPredence()
		{
			return precedence;
		}
	};

	struct AdditionOperator : Operator
	{
		explicit AdditionOperator(BaseOP* left)
			: Operator(left)
		{
			precedence = 10;
		}

		double calc() override {
			return left->execute() + right->execute();
		};
	};

	struct SubtractionOperator : Operator
	{
		explicit SubtractionOperator(BaseOP* left)
			: Operator(left)
		{
			precedence = 10;
		}


		double calc() override {
			return left->execute() - right->execute();
		};
	};

	struct MultiplicationOperator : Operator
	{
		explicit MultiplicationOperator(BaseOP* left)
			: Operator(left)
		{
			precedence = 20;
		}


		double calc() override {
			return left->execute() * right->execute();
		};
	};

	struct DivisionOperator : Operator
	{
		explicit DivisionOperator(BaseOP* left)
			: Operator(left)
		{
			precedence = 20;
		}


		double calc() override {
			if(right->execute() == 0)
			{
				return 0;
			}
			return left->execute() / right->execute();
		};
	};
}
