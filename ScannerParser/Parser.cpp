

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const wchar_t* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::moyaFTW() {
		Expect(28);
		Expect(47);
		while (la->kind == 18) {
			Class();
		}
		Main();
		Expect(48);
}

void Parser::Class() {
		Expect(18);
		Expect(1);
		if (la->kind == 13) {
			Get();
			Expect(1);
		}
		ClassBody();
}

void Parser::Main() {
		Expect(27);
		Expect(47);
		while (StartOf(1)) {
			Vars();
		}
		while (StartOf(2)) {
			Estatuto();
		}
		Expect(48);
}

void Parser::ClassBody() {
		Expect(47);
		while (StartOf(1)) {
			Vars();
		}
		while (StartOf(3)) {
			Metodo();
		}
		Expect(48);
}

void Parser::Vars() {
		A();
}

void Parser::Metodo() {
		if (la->kind == 21) {
			Get();
		} else if (StartOf(4)) {
			Tipo();
		} else SynErr(54);
		Expect(1);
		Expect(49);
		TipoParametros();
		Expect(50);
		Expect(47);
		Vars();
		while (StartOf(2)) {
			Estatuto();
		}
		Expect(22);
		if (StartOf(5)) {
			Expresion();
		}
		Expect(48);
}

void Parser::Estatuto() {
		if (la->kind == 9) {
			If();
		} else if (la->kind == 19) {
			For();
		} else if (la->kind == 10) {
			While();
		} else if (la->kind == 1) {
			AsignarLlamar();
		} else if (la->kind == 26) {
			Print();
		} else SynErr(55);
}

void Parser::A() {
		if (StartOf(4)) {
			Tipo();
			B();
			Expect(44);
		} else if (la->kind == 1) {
			DeclararObj();
		} else SynErr(56);
}

void Parser::Tipo() {
		if (la->kind == 6) {
			Get();
		} else if (la->kind == 12) {
			Get();
		} else if (la->kind == 7) {
			Get();
		} else if (la->kind == 11) {
			Get();
		} else if (la->kind == 8) {
			Get();
		} else SynErr(57);
}

void Parser::B() {
		Expect(1);
		if (la->kind == 37 || la->kind == 51) {
			E();
		}
}

void Parser::DeclararObj() {
		Expect(1);
		if (la->kind == 37) {
			Instanciar();
		}
		Expect(44);
}

void Parser::E() {
		if (la->kind == 37) {
			Get();
			Var_cte();
			if (la->kind == 45) {
				Get();
				B();
			}
		} else if (la->kind == 51) {
			Get();
			Expect(52);
			if (StartOf(4)) {
				InstanciarList();
			}
		} else SynErr(58);
}

void Parser::Var_cte() {
		switch (la->kind) {
		case 1: {
			Get();
			while (la->kind == 46) {
				Get();
				Expect(1);
			}
			if (StartOf(6)) {
				F();
			}
			break;
		}
		case 2: {
			Get();
			break;
		}
		case 5: {
			Get();
			break;
		}
		case 16: {
			Get();
			break;
		}
		case 17: {
			Get();
			break;
		}
		case 3: {
			Get();
			break;
		}
		case 4: {
			Get();
			break;
		}
		default: SynErr(59); break;
		}
}

void Parser::InstanciarList() {
		Tipo();
		Expect(51);
		Var_cte();
		Expect(52);
}

void Parser::Expresion() {
		Expresion_Otr();
		if (la->kind == 30 || la->kind == 31) {
			if (la->kind == 30) {
				Get();
			} else {
				Get();
			}
			Expresion();
		}
}

void Parser::Expresion_Otr() {
		Exp();
		if (StartOf(7)) {
			C();
		}
}

void Parser::Exp() {
		Termino();
		if (la->kind == 39 || la->kind == 40) {
			if (la->kind == 39) {
				Get();
			} else {
				Get();
			}
			Exp();
		}
}

void Parser::C() {
		Comparador();
		Exp();
}

void Parser::Comparador() {
		switch (la->kind) {
		case 32: {
			Get();
			break;
		}
		case 33: {
			Get();
			break;
		}
		case 34: {
			Get();
			break;
		}
		case 35: {
			Get();
			break;
		}
		case 36: {
			Get();
			break;
		}
		case 37: {
			Get();
			break;
		}
		default: SynErr(60); break;
		}
}

void Parser::Termino() {
		Factor();
		if (la->kind == 41 || la->kind == 42) {
			if (la->kind == 41) {
				Get();
			} else {
				Get();
			}
			Termino();
		}
}

void Parser::Factor() {
		D();
}

void Parser::F() {
		if (StartOf(5)) {
			Parametros();
		} else if (la->kind == 51) {
			Get();
			Var_cte();
			Expect(52);
		} else SynErr(61);
}

void Parser::Parametros() {
		Exp();
		if (la->kind == 45) {
			Get();
			Exp();
		}
}

void Parser::D() {
		if (la->kind == 49) {
			Get();
			Expresion();
			Expect(50);
		} else if (StartOf(8)) {
			if (la->kind == 39 || la->kind == 40 || la->kind == 43) {
				if (la->kind == 39) {
					Get();
				} else if (la->kind == 40) {
					Get();
				} else {
					Get();
				}
			}
			Var_cte();
		} else SynErr(62);
}

void Parser::If() {
		Expect(9);
		Expect(49);
		Expresion();
		Expect(50);
		Expect(47);
		while (StartOf(2)) {
			Estatuto();
		}
		Expect(48);
		if (la->kind == 15) {
			Get();
			Expect(47);
			while (StartOf(2)) {
				Estatuto();
			}
			Expect(48);
		}
}

void Parser::While() {
		Expect(10);
		Expect(49);
		Expresion();
		Expect(50);
		Expect(47);
		while (StartOf(2)) {
			Estatuto();
		}
		Expect(48);
}

void Parser::For() {
		Expect(19);
		Expect(49);
		if (la->kind == 1) {
			For1();
		}
		Expect(44);
		Expresion();
		Expect(44);
		if (la->kind == 1) {
			For1();
		}
		Expect(50);
		Expect(47);
		while (StartOf(2)) {
			Estatuto();
		}
		Expect(48);
}

void Parser::For1() {
		Expect(1);
		while (la->kind == 46) {
			Get();
			Expect(1);
		}
		if (StartOf(6)) {
			F();
		}
		Asignar();
}

void Parser::Asignar() {
		Expect(37);
		if (StartOf(5)) {
			Expresion();
		} else if (la->kind == 37) {
			Instanciar();
		} else if (la->kind == 29) {
			Read();
		} else SynErr(63);
}

void Parser::AsignarLlamar() {
		Expect(1);
		while (la->kind == 46) {
			Get();
			Expect(1);
		}
		if (StartOf(6)) {
			F();
		}
		if (la->kind == 37) {
			Asignar();
		}
		Expect(44);
}

void Parser::Instanciar() {
		Expect(37);
		Expect(23);
		if (la->kind == 1) {
			InstanciarObj();
		} else if (StartOf(4)) {
			InstanciarList();
		} else SynErr(64);
}

void Parser::Read() {
		Expect(29);
		Expect(49);
		Expect(50);
}

void Parser::Print() {
		Expect(26);
		Expect(49);
		Exp();
		Expect(50);
		Expect(44);
}

void Parser::TipoParametros() {
		Tipo();
		Expect(1);
		if (la->kind == 45) {
			Get();
			TipoParametros();
		}
}

void Parser::InstanciarObj() {
		Expect(1);
		Expect(49);
		if (StartOf(5)) {
			Parametros();
		}
		Expect(50);
}




// If the user declared a method Init and a mehtod Destroy they should
// be called in the contructur and the destructor respctively.
//
// The following templates are used to recognize if the user declared
// the methods Init and Destroy.

template<typename T>
struct ParserInitExistsRecognizer {
	template<typename U, void (U::*)() = &U::Init>
	struct ExistsIfInitIsDefinedMarker{};

	struct InitIsMissingType {
		char dummy1;
	};
	
	struct InitExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static InitIsMissingType is_here(...);

	// exist only if ExistsIfInitIsDefinedMarker is defined
	template<typename U>
	static InitExistsType is_here(ExistsIfInitIsDefinedMarker<U>*);

	enum { InitExists = (sizeof(is_here<T>(NULL)) == sizeof(InitExistsType)) };
};

template<typename T>
struct ParserDestroyExistsRecognizer {
	template<typename U, void (U::*)() = &U::Destroy>
	struct ExistsIfDestroyIsDefinedMarker{};

	struct DestroyIsMissingType {
		char dummy1;
	};
	
	struct DestroyExistsType {
		char dummy1; char dummy2;
	};

	// exists always
	template<typename U>
	static DestroyIsMissingType is_here(...);

	// exist only if ExistsIfDestroyIsDefinedMarker is defined
	template<typename U>
	static DestroyExistsType is_here(ExistsIfDestroyIsDefinedMarker<U>*);

	enum { DestroyExists = (sizeof(is_here<T>(NULL)) == sizeof(DestroyExistsType)) };
};

// The folloing templates are used to call the Init and Destroy methods if they exist.

// Generic case of the ParserInitCaller, gets used if the Init method is missing
template<typename T, bool = ParserInitExistsRecognizer<T>::InitExists>
struct ParserInitCaller {
	static void CallInit(T *t) {
		// nothing to do
	}
};

// True case of the ParserInitCaller, gets used if the Init method exists
template<typename T>
struct ParserInitCaller<T, true> {
	static void CallInit(T *t) {
		t->Init();
	}
};

// Generic case of the ParserDestroyCaller, gets used if the Destroy method is missing
template<typename T, bool = ParserDestroyExistsRecognizer<T>::DestroyExists>
struct ParserDestroyCaller {
	static void CallDestroy(T *t) {
		// nothing to do
	}
};

// True case of the ParserDestroyCaller, gets used if the Destroy method exists
template<typename T>
struct ParserDestroyCaller<T, true> {
	static void CallDestroy(T *t) {
		t->Destroy();
	}
};

void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create(L"Dummy Token");
	Get();
	moyaFTW();
	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 53;

	ParserInitCaller<Parser>::CallInit(this);
	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[9][55] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,x, x,x,T,T, T,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,x,x, x,x,x,x, x,T,T,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,T,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,T,T, T,x,x,T, T,x,x,x, x,x,x,x, x,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,x,x,x, x,x,T,T, T,x,x,T, T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,T,x,x, x,x,x,x, x,x,x,x, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,T, x,x,x,x, x,T,x,x, x,x,x},
		{x,T,T,T, T,T,x,x, x,x,x,x, x,x,x,x, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,T, x,x,x,x, x,T,x,T, x,x,x},
		{x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, T,T,T,T, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x},
		{x,T,T,T, T,T,x,x, x,x,x,x, x,x,x,x, T,T,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,T, T,x,x,T, x,x,x,x, x,x,x,x, x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	ParserDestroyCaller<Parser>::CallDestroy(this);
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	wchar_t* s;
	switch (n) {
			case 0: s = coco_string_create(L"EOF expected"); break;
			case 1: s = coco_string_create(L"id expected"); break;
			case 2: s = coco_string_create(L"cte_i expected"); break;
			case 3: s = coco_string_create(L"cte_char expected"); break;
			case 4: s = coco_string_create(L"cte_string expected"); break;
			case 5: s = coco_string_create(L"cte_d expected"); break;
			case 6: s = coco_string_create(L"int expected"); break;
			case 7: s = coco_string_create(L"char expected"); break;
			case 8: s = coco_string_create(L"string expected"); break;
			case 9: s = coco_string_create(L"if expected"); break;
			case 10: s = coco_string_create(L"while expected"); break;
			case 11: s = coco_string_create(L"bool expected"); break;
			case 12: s = coco_string_create(L"double expected"); break;
			case 13: s = coco_string_create(L"extends expected"); break;
			case 14: s = coco_string_create(L"this expected"); break;
			case 15: s = coco_string_create(L"else expected"); break;
			case 16: s = coco_string_create(L"false expected"); break;
			case 17: s = coco_string_create(L"true expected"); break;
			case 18: s = coco_string_create(L"class expected"); break;
			case 19: s = coco_string_create(L"for expected"); break;
			case 20: s = coco_string_create(L"do expected"); break;
			case 21: s = coco_string_create(L"void expected"); break;
			case 22: s = coco_string_create(L"return expected"); break;
			case 23: s = coco_string_create(L"new expected"); break;
			case 24: s = coco_string_create(L"null expected"); break;
			case 25: s = coco_string_create(L"super expected"); break;
			case 26: s = coco_string_create(L"write expected"); break;
			case 27: s = coco_string_create(L"main expected"); break;
			case 28: s = coco_string_create(L"ftw expected"); break;
			case 29: s = coco_string_create(L"read expected"); break;
			case 30: s = coco_string_create(L"and expected"); break;
			case 31: s = coco_string_create(L"or expected"); break;
			case 32: s = coco_string_create(L"lt expected"); break;
			case 33: s = coco_string_create(L"gt expected"); break;
			case 34: s = coco_string_create(L"lte expected"); break;
			case 35: s = coco_string_create(L"gte expected"); break;
			case 36: s = coco_string_create(L"ne expected"); break;
			case 37: s = coco_string_create(L"eq expected"); break;
			case 38: s = coco_string_create(L"ee expected"); break;
			case 39: s = coco_string_create(L"plus expected"); break;
			case 40: s = coco_string_create(L"minus expected"); break;
			case 41: s = coco_string_create(L"times expected"); break;
			case 42: s = coco_string_create(L"divide expected"); break;
			case 43: s = coco_string_create(L"not expected"); break;
			case 44: s = coco_string_create(L"scolon expected"); break;
			case 45: s = coco_string_create(L"comma expected"); break;
			case 46: s = coco_string_create(L"dot expected"); break;
			case 47: s = coco_string_create(L"lbrace expected"); break;
			case 48: s = coco_string_create(L"rbrace expected"); break;
			case 49: s = coco_string_create(L"lparent expected"); break;
			case 50: s = coco_string_create(L"rparent expected"); break;
			case 51: s = coco_string_create(L"lcorch expected"); break;
			case 52: s = coco_string_create(L"rcorch expected"); break;
			case 53: s = coco_string_create(L"??? expected"); break;
			case 54: s = coco_string_create(L"invalid Metodo"); break;
			case 55: s = coco_string_create(L"invalid Estatuto"); break;
			case 56: s = coco_string_create(L"invalid A"); break;
			case 57: s = coco_string_create(L"invalid Tipo"); break;
			case 58: s = coco_string_create(L"invalid E"); break;
			case 59: s = coco_string_create(L"invalid Var_cte"); break;
			case 60: s = coco_string_create(L"invalid Comparador"); break;
			case 61: s = coco_string_create(L"invalid F"); break;
			case 62: s = coco_string_create(L"invalid D"); break;
			case 63: s = coco_string_create(L"invalid Asignar"); break;
			case 64: s = coco_string_create(L"invalid Instanciar"); break;

		default:
		{
			wchar_t format[20];
			coco_swprintf(format, 20, L"error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const wchar_t *s) {
	wprintf(L"-- line %d col %d: %ls\n", line, col, s);
}

void Errors::Warning(const wchar_t *s) {
	wprintf(L"%ls\n", s);
}

void Errors::Exception(const wchar_t* s) {
	wprintf(L"%ls", s); 
	exit(1);
}


