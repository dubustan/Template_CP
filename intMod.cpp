struct intMod {
	const int mod = 1e9 + 7;
	int val;
	intMod(){};
	intMod(int val): val(val) {};
	bool operator == (const intMod &a) const { return a.val == val; }
	bool operator != (const intMod &a) const { return a.val != val; }
	void operator = (const int &a) {val = a;}
	void operator = (const intMod &a) {val = a.val;}
	intMod operator + (const intMod &other) { 
		val += other.val; 
		if(val >= mod) val -= mod; 
		return val;
	}
	intMod operator - (const intMod &other) { 
		val -= other.val; 
		if(val < 0) val += mod; 
		return val;
	}
	intMod operator * (const intMod &other) {
		return (long long)val * other.val % mod;
	}
	intMod bpow(int x) const {
		intMod ans(1), cc(val); 
		for(; x > 0; x >>= 1, cc = cc * cc) {
			if (x & 1) ans = ans * cc;
		}
		return ans;
	}
	intMod operator / (const intMod &other) { 
		return intMod(val) * other.bpow(mod - 2);
	}
	void operator += (const intMod &other) {(*this) = (*this) + other.val;}
	void operator -= (const intMod &other) {(*this) = (*this) - other.val;}
	void operator ++ () {(*this) += 1;}
	void operator -- () {(*this) -= 1;}
};

istream& operator >> (istream& inp, intMod& a) { inp >> a.val; return inp;}
ostream& operator << (ostream& out, const intMod &b) { out << b.val; return out;}
