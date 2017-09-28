<?php

/**
 * @file
 * Utility functions.
 */

/* Set the default CModel and DSID assignments.
 *
 * @return string
 *   The default DSID assignments
 */
function islandora_usage_stats_callbacks_set_default_dsids() {
  $default_dsids = "ir:citationCModel|PDF\nir:thesisCModel|PDF\nislandora:sp_pdf|OBJ
islandora:sp_basic_image|OBJ
islandora:sp_large_image_cmodel|OBJ
islandora:binaryObjectCModel|OBJ
islandora:sp_videoCModel|MP4
islandora:sp-audioCModel|PROXY_MP3
islandora:collectionCModel|FALSE
islandora:compoundCModel|FALSE
islandora:newspaperIssueCModel|PDF
islandora:newspaperPageCModel|OBJ
islandora:sp_web_archive|OBJ
islandora:sp_disk_image|OBJ
islandora:pageCModel|OBJ
islandora:bookCModel|PDF\nislandora:newspaperCModel|PDF";
  return $default_dsids;
}
