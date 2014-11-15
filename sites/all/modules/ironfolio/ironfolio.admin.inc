<?php
/**
 * Created by JetBrains PhpStorm.
 * User: 2kish
 * Date: 12.11.14
 * Time: 22:12
 * To change this template use File | Settings | File Templates.
 */

require_once 'ironfolio-lib.php';

function admin_ironfolio() {

    $ironFolioModel = new IronFolioModel;

    $current_cat = taxonomy_term_load(arg(2));
    $current_cat_id = $current_cat ? $current_cat->tid : null;

    // get language code
    global $language;
    $lang = $language->language;

    // get categories
    $categories = $ironFolioModel->getFolioCategories($lang);
    if (!$current_cat_id) {
        $current_cat_id = $categories[0]->tid;
    }

    // get folio items by lang and cat
    $iron_folio_items = $ironFolioModel->getFolioItemsByCatAndLang($current_cat_id, $lang);

    return theme('ironfolio_admin_list', array('categories' => $categories,
        'current_cat_id' => $current_cat_id,
        'iron_folio_items' => $iron_folio_items)
    );
}

function admin_ironfolio_changesortorder() {
    $nid1 = arg(3);
    $nid2 = arg(4);
    $ironFolioModel = new IronFolioModel;
    $changed = $ironFolioModel->changeSortOrder($nid1, $nid2);
    if ($changed) {
        drupal_set_message(t('Saved'), $type = 'status');
        drupal_goto($_SERVER['HTTP_REFERER']);
    } else {
        drupal_set_message('Error on saving', $type = 'error');
        drupal_goto($_SERVER['HTTP_REFERER']);
    }
}