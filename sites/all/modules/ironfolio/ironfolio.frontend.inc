<?php
require_once 'ironfolio-lib.php';
require_once 'ironfolio-helper.php';
function frontend_ironfolio() {

    $page = isset($_REQUEST['page']) ? (int) $_REQUEST['page'] : 1 ;
    $pageLimit = 2;
    $offset = ($page -1) * $pageLimit;

    $ironFolioModel = new IronFolioModel;

    $current_cat = taxonomy_term_load(arg(1));
    $current_cat_id = $current_cat ? $current_cat->tid : null;

    // get language code
    global $language;
    $lang = $language->language;

    // get categories
    $categories = $ironFolioModel->getFolioCategories($lang);
    if (!$current_cat_id) {
        $current_cat_id = $categories[0]->tid;
    }

    $iron_folio_items_all = $ironFolioModel->getFolioItemsByCatAndLang($current_cat_id, $lang);
    $iron_folio_items_all_count = count($iron_folio_items_all);
    unset($iron_folio_items_all);

    // get folio items by lang and cat
    $iron_folio_items = $ironFolioModel->getFolioItemsByCatAndLang($current_cat_id, $lang, $offset, $pageLimit);

    $helper = new IronFolioHelper;

    $pageCount = (int) floor($iron_folio_items_all_count / $pageLimit);
    if (($iron_folio_items_all_count % $pageLimit) > 0) {
        $pageCount++;
    }

    $pager = array('pageCount' => $pageCount,
        'page' => $page,);

    return theme('ironfolio_frontend_list', array('categories' => $categories,
            'current_cat_id'   => $current_cat_id,
            'iron_folio_items' => $iron_folio_items,
            'helper'           => $helper,
            'pager'           => $pager
        )
    );
}