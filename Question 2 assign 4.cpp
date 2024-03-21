#include <iostream>
#include <vector>
#include <algorithm>

class Term {
public:
    Term(double coef = 0.0, int exp = 0) : coefficient(coef), exponent(exp) {}
    double getCoefficient() const { return coefficient; }
    int getExponent() const { return exponent; }
    void setCoefficient(double coef) { coefficient = coef; }
    void setExponent(int exp) { exponent = exp; }
private:
    double coefficient;
    int exponent;
};

class Polynomial {
public:
    Polynomial() {}
    Polynomial(const std::vector<Term>& terms) : terms(terms) {}
    void setTerms(const std::vector<Term>& t) { terms = t; }
    std::vector<Term> getTerms() const { return terms; }
    void print() const;
    
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

private:
    std::vector<Term> terms;
};

void Polynomial::print() const {
    bool firstTerm = true;
    for (const auto& term : terms) {
        if (term.getCoefficient() != 0) {
            if (!firstTerm && term.getCoefficient() > 0)
                std::cout << "+ ";
            std::cout << term.getCoefficient() << "x^" << term.getExponent() << " ";
            firstTerm = false;
        }
    }
    std::cout << std::endl;
}

Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result;
    std::vector<Term> resultTerms;
    std::merge(terms.begin(), terms.end(), other.terms.begin(), other.terms.end(), std::back_inserter(resultTerms),
               [](const Term& a, const Term& b) { return a.getExponent() > b.getExponent(); });
    result.setTerms(resultTerms);
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result;
    std::vector<Term> negatedTerms;
    for (const auto& term : other.getTerms()) {
        negatedTerms.push_back(Term(-term.getCoefficient(), term.getExponent()));
    }
    std::vector<Term> resultTerms;
    std::merge(terms.begin(), terms.end(), negatedTerms.begin(), negatedTerms.end(), std::back_inserter(resultTerms),
               [](const Term& a, const Term& b) { return a.getExponent() > b.getExponent(); });
    result.setTerms(resultTerms);
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;
    std::vector<Term> resultTerms;
    for (const auto& term1 : terms) {
        for (const auto& term2 : other.terms) {
            double coef = term1.getCoefficient() * term2.getCoefficient();
            int exp = term1.getExponent() + term2.getExponent();
            resultTerms.push_back(Term(coef, exp));
        }
    }
    result.setTerms(resultTerms);
    return result;
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        terms = other.terms;
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    *this = *this + other;
    return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
    *this = *this - other;
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    *this = *this * other;
    return *this;
}

int main() {
    Polynomial p1({Term(2, 4), Term(-3, 2), Term(5, 0)});
    Polynomial p2({Term(3, 3), Term(1, 2), Term(2, 0)});
    
    Polynomial sum = p1 + p2;
    std::cout << "Sum: ";
    sum.print();
    
    Polynomial diff = p1 - p2;
    std::cout << "Difference: ";
    diff.print();
    
    Polynomial prod = p1 * p2;
    std::cout << "Product: ";
    prod.print();
    
    return 0;
}
