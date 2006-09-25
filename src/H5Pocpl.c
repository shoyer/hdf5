/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdf.ncsa.uiuc.edu/HDF5/doc/Copyright.html.  If you do not have     *
 * access to either file, you may request a copy from hdfhelp@ncsa.uiuc.edu. *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define H5P_PACKAGE		/*suppress error about including H5Ppkg	  */

/* Private header files */
#include "H5private.h"		/* Generic Functions			*/
#include "H5Eprivate.h"		/* Error handling		  	*/
#include "H5Iprivate.h"		/* IDs			  		*/
#include "H5Ppkg.h"		/* Property lists		  	*/

/* Local datatypes */

/* Static function prototypes */


/*-------------------------------------------------------------------------
 * Function:    H5Pset_copy_object
 *
 * Purpose:     Set properties when copying an object (group, dataset, and datatype)
 *              from one location to another
 *
 * Usage:       H5Pset_copy_group(plist_id, cpy_option)
 *              hid_t plist_id;			IN: Property list to copy object
 *              unsigned cpy_option; 		IN: Options to copy object such as
 *                  H5G_COPY_SHALLOW_HIERARCHY_FLAG    -- Copy only immediate members
 *                  H5G_COPY_EXPAND_SOFT_LINK_FLAG     -- Expand soft links into new objects/
 *                  H5G_COPY_EXPAND_EXT_LINK_FLAG      -- Expand external links into new objects
 *                  H5G_COPY_EXPAND_REFERENCE_FLAG -- Copy objects that are pointed by references
 *                  H5G_COPY_WITHOUT_ATTR_FLAG         -- Copy object without copying attributes
*
 * Return:      Non-negative on success/Negative on failure
 *
 * Programmer:  Peter Cao
 *              March 13, 2006
 *-------------------------------------------------------------------------
 */
herr_t
H5Pset_copy_object(hid_t plist_id, unsigned cpy_option)
{
    H5P_genplist_t *plist;      /* Property list pointer */
    herr_t ret_value = SUCCEED; /* Return value */

    FUNC_ENTER_API(H5Pset_copy_object, FAIL)
    H5TRACE2("e","iIu",plist_id,cpy_option);

    /* Check parameters */
    if(cpy_option & ~H5G_COPY_ALL)
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "unknown option specified")

    /* Get the plist structure */
    if(NULL == (plist = H5P_object_verify(plist_id, H5P_OBJECT_COPY)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")

    /* Set value */
    if(H5P_set(plist, H5G_CPY_OPTION_NAME, &cpy_option) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTSET, FAIL, "can't set copy object flag")

done:
    FUNC_LEAVE_API(ret_value)
} /* end H5Pset_copy_object() */


/*-------------------------------------------------------------------------
 * Function:    H5Pget_copy_object
 *
 * Purpose:     Returns the cpy_option, which is set for H5Gcopy(hid_t loc_id,
 *              const char* name, ... ) for copying objects
 *
 * Return:      Non-negative on success/Negative on failure
 *
 * Programmer:  Peter Cao
 *              March 13, 2006
 *-------------------------------------------------------------------------
 */
herr_t
H5Pget_copy_object(hid_t plist_id, unsigned *cpy_option /*out*/)
{
    H5P_genplist_t *plist;      /* Property list pointer */
    herr_t ret_value = SUCCEED; /* return value */

    FUNC_ENTER_API(H5Pget_copy_object, FAIL)
    H5TRACE2("e","ix",plist_id,cpy_option);

    /* Get the plist structure */
    if(NULL == (plist = H5P_object_verify(plist_id, H5P_OBJECT_COPY)))
        HGOTO_ERROR(H5E_ATOM, H5E_BADATOM, FAIL, "can't find object for ID")

    /* Get values */
    if(cpy_option)
        if(H5P_get(plist, H5G_CPY_OPTION_NAME, cpy_option) < 0)
            HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get object copy flag")

done:
    FUNC_LEAVE_API(ret_value)
} /* end H5Pget_copy_object() */

