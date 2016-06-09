/*****************************************************************************\
 Tara -- 

 Copyright (C) 2009  Niels Lohmann <niels.lohmann@uni-rostock.de>

 Tara is free software: you can redistribute it and/or modify it under the
 terms of the GNU Affero General Public License as published by the Free
 Software Foundation, either version 3 of the License, or (at your option)
 any later version.

 Tara is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public License for
 more details.

 You should have received a copy of the GNU Affero General Public License
 along with Tara.  If not, see <http://www.gnu.org/licenses/>.
\*****************************************************************************/


/*
NOTE: This syntax-scanner does not recognize semantic errors!
Wrong Input causes undefined behaviour and not necessarily an error message.
*/

%token KW_STATE KW_LOWLINK KW_SCC COLON COMMA ARROW NUMBER NAME

%expect 0
%defines
%name-prefix="graph_"

%{
#include <string>
#include <stdio.h>
#include <pnapi/pnapi.h>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <utility>

extern int graph_lex();
extern int graph_error(const char *);

%}

%union {
  unsigned int val;
  char* str;
}

%type <val> NUMBER
%type <str> NAME
%type <val> lowlink

%%

states:
  state
| states state

;

state:
  KW_STATE NUMBER lowlink scc markings
    { }
    transitions
    { /* do nothing */  }
;

scc:
  /* empty */
| KW_SCC scc_members
;

scc_members:
  scc_member
| scc_members scc_member
;

scc_member:
  NUMBER 
;

lowlink:
  KW_LOWLINK NUMBER
    { $$ = $2; }
;

markings:
markingList
;

markingList:
 marking
| markingList COMMA marking
;

marking:
  NAME COLON NUMBER
  {  }
;

transitions:
  /* empty */
| transitionList
;

transitionList:
  transition
| transitionList transition
;

transition:
  NAME ARROW NUMBER 
  {  }
;
