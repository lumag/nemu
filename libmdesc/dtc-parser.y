/*
 * dtc-parser.y
 *
 * Copyright (C) 2009 Dmitry Eremin-Solenikov
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


%locations
%debug

%{
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

extern int yyerror(const char *message);

int yydebug = 0;

%}

%code requires {
extern int yylex(void);
}

%token DTS_V1;
%token DTS_PROPNAME;
%token DTS_STRING;
%token DTS_LITERAL;

%%

input:	DTS_V1 ';' devicetree
     ;

devicetree: '/' node
	  ;

node:	'{' props subnodes '}' ';'
    ;

props:	/* empty */
     |	props prop
     ;

prop:	DTS_PROPNAME '=' propdata ';'
    |	DTS_PROPNAME ';'
    ;

propdata:	DTS_STRING
	|	'<' celllist '>'
	;

celllist:	/* empty */
       |	celllist DTS_LITERAL
       ;

subnodes:	/* empty */
	|	subnode subnodes
	;

subnode:	DTS_PROPNAME node
       ;

%%
