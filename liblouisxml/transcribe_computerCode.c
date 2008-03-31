/* liblouisxml xml to Braille Translation Library

   This file may contain code borrowed from the Linux screenreader
   BRLTTY, copyright (C) 1999-2006 by
   the BRLTTY Team

   Copyright (C) 2004, 2005, 2006
   ViewPlus Technologies, Inc. www.viewplus.com
   and
   JJB Software, Inc. www.jjb-software.com
   All rigets reserved

   This file is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

In addition to the permissions and restrictions contained in the GNU
General Public License (GPL), the copyright holders grant two explicit
permissions and impose one explicit restriction. The permissions are:

1) Using, copying, merging, publishing, distributing, sublicensing, 
   and/or selling copies of this software that are either compiled or loaded 
   as part of and/or linked into other code is not bound by the GPL.

2) Modifying copies of this software as needed in order to facilitate 
   compiling and/or linking with other code is not bound by the GPL.

The restriction is:

3. The translation, semantic-action and configuration tables that are 
   read at run-time are considered part of this code and are under the terms 
   of the GPL. Any changes to these tables and any additional tables that are 
   created for use by this code must be made publicly available.

All other uses, including modifications not required for compiling or linking 
and distribution of code which is not linked into a combined executable, are 
bound by the terms of the GPL.

   This file is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.

   Maintained by John J. Boyer john.boyer@jjb-software.cem

*/

#include <stdio.h>
#include <string.h>
#include "louisxml.h"

static int computerCodeEmptyElement (xmlNode * node, int action);
static void computerCodeText (xmlNode * node, int action);
static void computerCodeCdata (xmlNode * node);

int
transcribe_computerCode (xmlNode * node, int action)
{
  xmlNode *child;
  int branchCount = 0;
  if (action == 0 && (ud->text_length > 0 || ud->translated_length > 0))
    {
      StyleType *style;
      insert_translation (ud->mainBrailleTable);
      ud->top--;
      style = find_current_style ();
      ud->top++;
      if (style != NULL)
	write_paragraph (style->action);
      else
	write_paragraph (para);
    }
  push_sem_stack (node);
  switch (ud->stack[ud->top])
    {
    case skip:
      pop_sem_stack ();
      return 0;
    case code:
      break;
    default:
      break;
    }
  child = node->children;
  while (child)
    {
      switch (child->type)
	{
	case XML_ELEMENT_NODE:
	  insert_code (node, branchCount);
	  branchCount++;
	  if (child->children)
	    transcribe_computerCode (child, 1);
	  else
	    computerCodeEmptyElement (child, 1);
	  break;
	case XML_TEXT_NODE:
	  computerCodeText (child, 1);
	  break;
	case XML_CDATA_SECTION_NODE:
	  computerCodeCdata (child);
	  break;
	default:
	  break;
	}
      child = child->next;
    }
  insert_code (node, branchCount);
  insert_code (node, -1);
  pop_sem_stack ();
  if (action == 0)
    {
      memset (ud->typeform, computer_braille, ud->text_length);
      insert_translation (ud->compbrl_table_name);
      write_paragraph (code);
    }
  return 1;
}

static int
computerCodeEmptyElement (xmlNode * node, int action)
{
  push_sem_stack (node);
  switch (ud->stack[ud->top])
    {
    case softreturn:
      break;
    case boxline:
      break;
    case blankline:
      break;
    case newpage:
      break;
    case righthandpage:
      break;
    default:
      break;
    }
  pop_sem_stack ();
  return 1;
}

static void
computerCodeText (xmlNode * node, int action)
{
  insert_utf8 (node->content);
}

static void
computerCodeCdata (xmlNode * node)
{
  insert_utf8 (node->content);
}
