#pragma once
class Console
{

public:
	static Console& GetInstance()
	{
		static Console instance;
		return instance;
	}

// ΩÃ±€≈Ê ∆–≈œ¿ª ¿ß«ÿ... « ø‰«— ≥‡ºÆ... 
private:
	Console();
	~Console();

};

