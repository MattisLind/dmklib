/*
 * raw2dmk - write a dmk floppy image
 *
 * $Id: dmk2raw.c 41 2003-12-21 23:48:14Z eric $
 *
 * Copyright 2002 Eric Smith.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.  Note that permission is
 * not granted to redistribute this program under the terms of any
 * other version of the General Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111  USA
 */


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "libdmk.h"


void print_sector_info (sector_info_t *sector_info)
{
  printf ("cyl %d head %d sector %d size %d\n",
	  sector_info->cylinder,
	  sector_info->head,
	  sector_info->sector,
	  128 << sector_info->size_code);
}

/*
To create a image

dmk_create_image
for each track:
  dmk_seek
  dmk_format_track
  for each sector:
    dmk_read_id
    dmk_write_sector
*/

int main (int argc, char *argv[])
{
  dmk_handle h;
  FILE *inf;

  int ds, dd, rx02;
  int cylinders;

  int cylinder, head, sector;

  int sector_count;
  int min_sector, max_sector;
  sector_info_t sector_info [DMK_MAX_SECTOR];
  int sector_index [256];
 
  uint8_t buf [1024];

  int i;

  if (argc != 3)
    {
      fprintf (stderr, "usage: %s image.dmk image.raw\n", argv [0]);
      exit (1);
    }
  cylinders=77;
  ds=0;
  h = dmk_create_image (argv [2], ds, cylinders, 0, 360, 250, 1);
  if (! h)
    {
      fprintf (stderr, "error opening input DMK file\n");
      exit (2);
    }

  inf = fopen (argv [1], "rb");
  if (! inf)
    {
      fprintf (stderr, "error opening output raw file\n");
      exit (2);
    }

  for (cylinder = 0; cylinder < cylinders; cylinder++)
    for (head = 0; head <= ds; head++) {
	if (! dmk_seek (h, cylinder, head)) {
	    fprintf (stderr, "error seeking to cylinder %d\n", cylinder);
	    exit (2);
	}
	for (sector=0;sector<DMK_MAX_SECTOR; sector++) {
		sector_info[sector].cylinder = cylinder;
		sector_info[sector].head =head;
		sector_info[sector].sector =sector;
		sector_info[sector].size_code = 1;
		sector_info[sector].write_data =1;
		sector_info[sector].mode =DMK_RX02;
		sector_info[sector].data_value =0xe5;
	}  
  
	  
	if (! dmk_format_track (h, DMK_RX02, 26, &(sector_info[0]))) {
		fprintf (stderr, "error formatting cylinder %d head %d\n", cylinder,head);
	    exit (2);
	} 
	

	for (sector = 0; sector < 26; sector++) {

		fprintf (stderr, "size_code = %d\n", sector_info [sector].size_code);
		if (1 != fread (buf, 128 << (sector_info [sector].size_code), 1, inf)) {
		    fprintf (stderr, "error writing raw file\n");
		    exit (2);
		}
		fprintf (stderr, "222\n");
	    if (!dmk_write_sector (h, & sector_info [sector], buf)) {
			fprintf (stderr, "error writing cylinder %d head %d sector %d\n", cylinder,head, sector);
		}
	}
	}

  dmk_close_image (h);

  fclose (inf);

  exit (0);
}
