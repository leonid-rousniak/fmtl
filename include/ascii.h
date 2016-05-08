#pragma once

#include <array>
#include <string>
#include <vector>

namespace ascii
{

using Art = std::array<std::string,5>;

Art A = {
"    _    ", 
"   / \\   ",
"  / _ \\  ",
" / ___ \\ ",
"/_/   \\_\\"};

Art B = {
" ____  "
"| __ ) "
"|  _ \\ " 
"| |_) |"
"|____/ "};

Art C = {
"  ____ ",
" / ___|",
"| |    ",
"| |___ ",
" \\____|"};

Art D = {
" ____  ",
"|  _ \\ ",
"| | | |",
"| |_| |",
"|____/ "};

Art E = {
" _____ ",
"| ____|",
"|  _|  ",
"| |___ ",
"|_____|"};

Art F = {
" _____ ",
"|  ___|",
"| |_   ",
"|  _|  ",
"|_|    "};

Art G = {
"  ____ ",
" / ___|",
"| |  _ ",
"| |_| |",
" \\____|"};

Art H = {
" _   _ ",
"| | | |",
"| |_| |",
"|  _  |",
"|_| |_|"};

Art I = {
" ___ ",
"|_ _|",
" | | ",
" | | ",
"|___|"};

Art J = {
"     _ ",
"    | |",
" _  | |",
"| |_| |",
" \\___/ "};

Art K = {
" _  __",
"| |/ /",
"| ' / ",
"| . \\ ",
"|_|\\_\\"};

Art L = {
" _     ",
"| |    ",
"| |    ",
"| |___ ",
"|_____|"};

Art M = {
" __  __ ",
"|  \\/  |",
"| |\\/| |",
"| |  | |",
"|_|  |_|"};

Art N = {
" _   _ ",
"| \\ | |",
"|  \\| |",
"| |\\  |",
"|_| \\_|"};

Art O = {
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\___/ "};

Art P = {
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  __/ ",
"|_|    "};

Art Q = {
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\__\\_\\"};

Art R = {
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  _ < ",
"|_| \\_\\"};

Art S = {
" ____  ",
"/ ___| ",
"\\___ \\ ",
" ___) |",
"|____/ "};

Art T = {
" _____ ",
"|_   _|",
"  | |  ",
"  | |  ",
"  |_|  "};

Art U = {
" _   _ ",
"| | | |",
"| | | |",
"| |_| |",
" \\___/ "};

Art V = {
"__     __",
"\\ \\   / /",
" \\ \\ / / ",
"  \\ V /  ",
"   \\_/   "};

Art W = {
"__        __",
"\\ \\      / /",
" \\ \\ /\\ / / ",
"  \\ V  V /  ",
"   \\_/\\_/   "};

Art X = {
"__  __",
"\\ \\/ /",
" \\  / ",
" /  \\ ",
"/_/\\_\\"};

Art Y = {
"__   __",
"\\ \\ / /",
" \\ V / ",
"  | |  ",
"  |_|  "};

Art Z = {
" _____",
"|__  /",
"  / / ",
" / /_ ",
"/____|"};

Art convert(char chr)
{
	switch(chr) {
		case 'A': return A; break;
		case 'B': return B; break;
		case 'C': return C; break;
		case 'D': return D; break;
		case 'E': return E; break;
		case 'F': return F; break;
		case 'G': return G; break;
		case 'H': return H; break;
		case 'I': return I; break;
		case 'J': return J; break;
		case 'K': return K; break;
		case 'L': return L; break;
		case 'M': return M; break;
		case 'N': return N; break;
		case 'O': return O; break;
		case 'P': return P; break;
		case 'Q': return Q; break;
		case 'R': return R; break;
		case 'S': return S; break;
		case 'T': return T; break;
		case 'U': return U; break;
		case 'V': return V; break;
		case 'W': return W; break;
		case 'X': return X; break;
		case 'Y': return Y; break;
		case 'Z': return Z; break;
		default: return {"","","","",""};
	}
}


std::string generator(std::string text)
{
	std::vector<Art> word(text.size());
	for (uint32_t i = 0; i < text.size(); ++i)
		word[i] = convert(text.at(i));

	std::string wordStr;

	for (uint32_t i = 0; i < 5; ++i) {
		for (const Art& art : word)
			wordStr += art[i];
		wordStr.append(1,'\n');
	}

	return wordStr;
}



} // namespace ascii