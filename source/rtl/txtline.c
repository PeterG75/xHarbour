/*
 * $Id$
 */

/*
 * xHarbour Project source code:
 * hb_tabexpand() and hb_readline() functions
 *
 * Copyright 2004 Marcelo Lombardo - lombardo@uol.com.br
 * http://www.xharbour.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307 USA (or visit the web site http://www.gnu.org/).
 *
 * As a special exception, the Harbour Project gives permission for
 * additional uses of the text contained in its release of Harbour.
 *
 * The exception is that, if you link the Harbour libraries with other
 * files to produce an executable, this does not by itself cause the
 * resulting executable to be covered by the GNU General Public License.
 * Your use of that executable is in no way restricted on account of
 * linking the Harbour library code into it.
 *
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 *
 * This exception applies only to the code released by the Harbour
 * Project under the name Harbour.  If you copy code from other
 * Harbour Project or Free Software Foundation releases into a copy of
 * Harbour, as the General Public License permits, the exception does
 * not apply to the code that you add in this way.  To avoid misleading
 * anyone as to the status of such modified files, you must delete
 * this exception notice from them.
 *
 * If you write modifications of your own for Harbour, it is your choice
 * whether to permit this exception to apply to your modifications.
 * If you do not wish that, delete this exception notice.
 *
 */

#if defined( __WATCOMC__ )
   #pragma disable_message ( 136 )
#endif

#include <ctype.h>

#include "hbapi.h"
#include "hbapifs.h"
#include "hbfast.h"
#include "hbset.h"
#include "hbapiitm.h"
#include "hbapierr.h"

static void hb_readLine( const char * szText, HB_SIZE ulTextLen, HB_SIZE uiLineLen, HB_SIZE uiTabLen, BOOL bWrap, const char ** Term, HB_SIZE * iTermSizes, HB_SIZE uiTerms, BOOL * bFound, BOOL * bEOF, HB_ISIZ * lEnd, HB_SIZE * ulEndOffset )
{
   HB_SIZE   uiPosTerm, uiPosition;
   HB_SIZE   ulPos, ulCurrCol, ulLastBlk;
   BOOL     bBreak = 0;

   HB_TRACE( HB_TR_DEBUG, ( "hb_readLine(%p, %i, %i, %i, %i, %p, %p, %i, %i, %i, %i, %i)", szText, ulTextLen, uiLineLen, uiTabLen, bWrap, **Term, *iTermSizes, uiTerms, *bFound, *bEOF, *lEnd, *ulEndOffset ) );

   *bFound     = 0;
   *bEOF       = 0;
   *ulEndOffset   = 0;
   *lEnd       = 0;
   ulCurrCol   = 0;
   ulLastBlk   = 0;

   if( ulTextLen == 0 )
   {
      *lEnd          = -1;      
      *bEOF          = 1;
      return;
   }

   if( uiTabLen == 0 )
   {
      uiTabLen = 4;
   }

   for( ulPos = 0; ulPos < ulTextLen; ulPos++ )
   {
      // Check for line terminators
      for( uiPosTerm = 0; uiPosTerm < uiTerms; uiPosTerm++ )
      {
         if( szText[ ulPos ] == Term[ uiPosTerm ][ 0 ] && ( ulPos + iTermSizes[ uiPosTerm ] - 1 ) < ulTextLen )
         {
            *bFound = 1;

            for( uiPosition = 1; uiPosition < iTermSizes[ uiPosTerm ]; uiPosition++ )
            {
               if( Term[ uiPosTerm ][ uiPosition ] != szText[ ulPos + uiPosition ] )
               {
                  *bFound = 0;
                  break;
               }
            }

            if( *bFound )
            {
               if( ulPos == 0 )
               {
                  *lEnd          =  -1;
                  *ulEndOffset   = iTermSizes[ uiPosTerm ];
               }
               else
               {
                  *lEnd          = ulPos - 1;
                  *ulEndOffset   = ulPos + iTermSizes[ uiPosTerm ];
               }
               break;
            }
         }
      }

      if( szText[ ulPos ] == HB_CHAR_HT )
      {
         ulCurrCol += uiTabLen - ( ulCurrCol % uiTabLen );
      }
      else if( szText[ ulPos ] == HB_CHAR_SOFT1 && szText[ ulPos + 1 ] == HB_CHAR_SOFT2 )
      {
         // Clipper does NOT considers SOFT CR as a word seperator - WHY?
         // Should we not fix that?
         #if 0
         ulLastBlk = ulPos;
         #endif

         ulPos++;
      }
      else
      {
         ulCurrCol++;
      }

      if( *bFound )
      {
         break;
      }

      if( szText[ ulPos ] == ' ' || szText[ ulPos ] == HB_CHAR_HT )
      {
         ulLastBlk = ulPos;
      }

      if( ulCurrCol > uiLineLen )
      {
         if( bWrap == FALSE || ulLastBlk == 0 )
         {
            *lEnd          = ulPos - 1;
            *ulEndOffset   = ulPos;
            bBreak         = 1;
            break;
         }
         else if( bWrap && ulLastBlk != 0 )
         {
            *lEnd          = ulLastBlk;
            *ulEndOffset   = ulLastBlk + 1;
            bBreak         = 1;
            break;
         }
      }
   }

   if( *bFound == FALSE && bBreak == FALSE )
   {
      *lEnd          = ulTextLen - 1;
      *ulEndOffset   = ulTextLen - 1;
      *bEOF          = 1;
   }
}

static HB_ISIZ hb_tabexpand( const char * szString, char * szRet, HB_ISIZ lEnd, HB_SIZE uiTabLen )
{
   HB_ISIZ lPos, lSpAdded = 0;

   for( lPos = 0; lPos <=  lEnd; lPos++ )
   {
      if( szString[ lPos ] == HB_CHAR_HT )
      {
         lSpAdded += ( ( uiTabLen > 0 ) ? uiTabLen - ( ( lPos + lSpAdded ) % uiTabLen ) - 1 : 0 );
      }
      else if( ( lPos <  lEnd &&  szString[ lPos ] == HB_CHAR_SOFT1 && szString[ lPos + 1 ] == HB_CHAR_SOFT2 ) || szString[ lPos ] == HB_CHAR_LF )
      {
         lSpAdded--;
      }
      else
      {
         *( szRet + lPos + lSpAdded ) = *( szString + lPos );
      }
   }

   return  ( lSpAdded + lEnd );
}

HB_FUNC( HB_TABEXPAND )
{
   const char *   szText      = hb_parcx( 1 );
   HB_ISIZ        lStrLen     = hb_parclen( 1 );
   HB_SIZE         uiTabLen    =  hb_parns( 2 );
   HB_SIZE         uiTabCount  = 0;
   HB_ISIZ        lPos, lSize; 
   char *         szRet;

   for( lPos = 0; lPos < lStrLen; lPos++ )
   {
      if( szText[ lPos ] == HB_CHAR_HT )
      {
         uiTabCount++;
      }
   }

   if( ( lStrLen == 0 ) || ( uiTabCount == 0 ) || ( uiTabLen == 0 ) )
   {
      hb_retc( szText );
   }
   else
   {
      lSize    = lStrLen + uiTabCount * ( uiTabLen - 1 );
      szRet    = ( char * ) hb_xgrab( lSize + 1 );
      memset( szRet, ' ', ( size_t ) lSize );
      lStrLen  = hb_tabexpand( szText, szRet, lStrLen, uiTabLen );
      hb_retclenAdopt( szRet, lStrLen );
   }

}

// HB_READLINE( <cText>, [<aTerminators | cTerminator>], <nLineLen>, <nTabLen>, <lWrap>, [<nStartOffset>], @nOffSet, @nEnd, @lFound, @lEOF )
HB_FUNC( HB_READLINE )
{
   PHB_ITEM       pTerm1;
   const char *   szText = hb_parcx( 1 );
   const char **        Term;
   HB_SIZE *          iTermSizes;
   HB_SIZE         uiTabLen, uiTerms;
   HB_SIZE          ulLineSize  = hb_parni( 3 );
   HB_SIZE         i;
   BOOL           bWrap       = hb_parl( 5 );
   BOOL           bFound, bEOF;
   HB_SIZE          ulStartOffset;
   HB_SIZE        ulEndOffset, ulTextLen;
   HB_ISIZ        lEnd;
   PHB_ITEM        Opt;
   BOOL           bAlloc_Term1 = FALSE;

   if( ! ISCHAR( 1 ) )
   {
      hb_errRT_BASE_SubstR( EG_ARG, 3012, NULL, "READLINE", 9, hb_paramError( 1 ), hb_paramError( 2 ), hb_paramError( 3 ), hb_paramError( 4 ), hb_paramError( 5 ), hb_paramError( 6 ), hb_paramError( 7 ), hb_paramError( 8 ), hb_paramError( 9 ), hb_paramError( 10 ) );
      return;
   }

   ulTextLen   = hb_parclen( 1 );
   uiTabLen    = hb_parclen( 4 );

   if( ISNUM( 6 ) )
   {
      ulStartOffset = hb_parns( 6 );
   }
   else
   {
      ulStartOffset = 0;
   }

   if( ! ( ISARRAY( 2 ) || ISCHAR( 2 ) ) )
   {
      pTerm1         = hb_itemPutC( NULL, hb_setGetEOL() );
      bAlloc_Term1   = TRUE;
   }
   else
   {
      pTerm1 = hb_param( 2, HB_IT_ANY );
   }

   Opt = hb_itemNew( NULL );

   if( HB_IS_ARRAY( pTerm1 ) )
   {
      uiTerms     = hb_arrayLen( pTerm1 );
      Term        = ( const char ** ) hb_xgrab( sizeof( char * ) * uiTerms );
      iTermSizes  = ( HB_SIZE * ) hb_xgrab( sizeof( HB_SIZE ) * uiTerms );

      for( i = 0; i < uiTerms; i++ )
      {
         hb_arrayGet( pTerm1, i + 1, Opt );
         Term[ i ]         =  hb_itemGetCPtr( Opt );
         iTermSizes[ i ]   =  hb_itemGetCLen( Opt );
      }
   }
   else
   {
      Term              = ( const char ** ) hb_xgrab( sizeof( char * ) );
      iTermSizes        = ( HB_SIZE * ) hb_xgrab( sizeof( HB_SIZE ) * 1 );
      Term[ 0 ]         = hb_itemGetCPtr( pTerm1 );
      iTermSizes[ 0 ]   = hb_itemGetCLen( pTerm1 );
      uiTerms           = 1;
   }

   hb_itemRelease( Opt );  

   ulStartOffset--;

   hb_readLine( szText + ulStartOffset, ulTextLen - ulStartOffset, ulLineSize, uiTabLen, bWrap, Term, iTermSizes, uiTerms, &bFound, &bEOF, &lEnd, &ulEndOffset );

   hb_storl( bFound, 7 );
   hb_storl( bEOF, 8 );
   hb_storns( lEnd + ulStartOffset + 1, 9 );
   hb_storns( ulEndOffset + ulStartOffset + 1, 10 );

   if( bAlloc_Term1 )
   {
      hb_itemRelease( pTerm1 );
   }

   hb_xfree( (void*) Term );
   hb_xfree( iTermSizes );
}

