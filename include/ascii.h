#pragma once

#include <array>
#include <string>
#include <vector>

namespace ascii
{

using Art = std::array<std::string,5>;

const Art A = {
"    _    ", 
"   / \\   ",
"  / _ \\  ",
" / ___ \\ ",
"/_/   \\_\\"};

const Art B = {
" ____  "
"| __ ) "
"|  _ \\ " 
"| |_) |"
"|____/ "};

const Art C = {
"  ____ ",
" / ___|",
"| |    ",
"| |___ ",
" \\____|"};

const Art D = {
" ____  ",
"|  _ \\ ",
"| | | |",
"| |_| |",
"|____/ "};

const Art E = {
" _____ ",
"| ____|",
"|  _|  ",
"| |___ ",
"|_____|"};

const Art F = {
" _____ ",
"|  ___|",
"| |_   ",
"|  _|  ",
"|_|    "};

const Art G = {
"  ____ ",
" / ___|",
"| |  _ ",
"| |_| |",
" \\____|"};

const Art H = {
" _   _ ",
"| | | |",
"| |_| |",
"|  _  |",
"|_| |_|"};

const Art I = {
" ___ ",
"|_ _|",
" | | ",
" | | ",
"|___|"};

const Art J = {
"     _ ",
"    | |",
" _  | |",
"| |_| |",
" \\___/ "};

const Art K = {
" _  __",
"| |/ /",
"| ' / ",
"| . \\ ",
"|_|\\_\\"};

const Art L = {
" _     ",
"| |    ",
"| |    ",
"| |___ ",
"|_____|"};

const Art M = {
" __  __ ",
"|  \\/  |",
"| |\\/| |",
"| |  | |",
"|_|  |_|"};

const Art N = {
" _   _ ",
"| \\ | |",
"|  \\| |",
"| |\\  |",
"|_| \\_|"};

const Art O = {
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\___/ "};

const Art P = {
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  __/ ",
"|_|    "};

const Art Q = {
"  ___  ",
" / _ \\ ",
"| | | |",
"| |_| |",
" \\__\\_\\"};

const Art R = {
" ____  ",
"|  _ \\ ",
"| |_) |",
"|  _ < ",
"|_| \\_\\"};

const Art S = {
" ____  ",
"/ ___| ",
"\\___ \\ ",
" ___) |",
"|____/ "};

const Art T = {
" _____ ",
"|_   _|",
"  | |  ",
"  | |  ",
"  |_|  "};

const Art U = {
" _   _ ",
"| | | |",
"| | | |",
"| |_| |",
" \\___/ "};

const Art V = {
"__     __",
"\\ \\   / /",
" \\ \\ / / ",
"  \\ V /  ",
"   \\_/   "};

const Art W = {
"__        __",
"\\ \\      / /",
" \\ \\ /\\ / / ",
"  \\ V  V /  ",
"   \\_/\\_/   "};

const Art X = {
"__  __",
"\\ \\/ /",
" \\  / ",
" /  \\ ",
"/_/\\_\\"};

const Art Y = {
"__   __",
"\\ \\ / /",
" \\ V / ",
"  | |  ",
"  |_|  "};

const Art Z = {
" _____",
"|__  /",
"  / / ",
" / /_ ",
"/____|"};


const Art Zero = {
"  __  ",
" /  \\ ",
"| () |",
" \\__/ "};

const Art One = {
" _ ",
"/ |",
"| |",
"|_|"};

const Art Two = {
" ___ ",
"|_  )",
" / / ",
"/___|"};

const Art Three = {
" ____",
"|__ /",
" |_ \\",
"|___/"};

const Art Four = {
" _ _  ",
"| | | ",
"|_  _|",
"  |_| "};

const Art Five = {
" ___ ",
"| __|",
"|__ \\",
"|___/"};

const Art Six = {
"  __ ",
" / / ",
"/ _ \\",
"\\___/"};

const Art Seven = {
" ____ ",
"|__  |",
"  / / ",
" /_/  "};

const Art Eight = {
" ___ ",
"( _ )",
"/ _ \\",
"\\___/"};

const Art Nine = {
" ___ ",
"/ _ \\",
"\\_, /",
" /_/ "};

const Art Dot = {
"   ",
"   ",
" _ ",
"(_)"};

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
		case '0': return Zero; break;
		case '1': return One; break;
		case '2': return Two; break;
		case '3': return Three; break;
		case '4': return Four; break;
		case '5': return Five; break;
		case '6': return Six; break;
		case '7': return Seven; break;
		case '8': return Eight; break;
		case '9': return Nine; break;
		case '.': return Dot; break;
		default: return {"","","","",""};
	}
}


std::string generator(const std::string& text)
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
