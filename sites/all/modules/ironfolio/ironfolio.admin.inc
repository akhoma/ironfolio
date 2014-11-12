<?php
/**
 * Created by JetBrains PhpStorm.
 * User: 2kish
 * Date: 12.11.14
 * Time: 22:12
 * To change this template use File | Settings | File Templates.
 */

function admin_ironfolio() {

    $current_cat = taxonomy_term_load(arg(2));
    $current_cat_id = $current_cat ? $current_cat->tid : null;


    // get categories
    $vid = taxonomy_vocabulary_machine_name_load('folio_types ')->vid;
    $tax_tree = taxonomy_get_tree($vid);
    if (!$current_cat_id) {
        $current_cat_id = $tax_tree[0]->tid;
    }

    $categories = array();
    foreach ($tax_tree as $t_item) {
        $term = taxonomy_term_load($t_item->tid);
        $translated_term = i18n_taxonomy_localize_terms($term);
        $categories[] = $translated_term;
    }


    // get folio items by lang and cat
    global $language;
    $lang = $language->language;
    $nodes = node_load_multiple(array(), array('type' => 'iron_folio', 'language' => $lang));

    $iron_folio_items = array();
    foreach ($nodes as $node) {
        if ($node->field_category['und'][0]['tid'] == $current_cat_id) {
            $iron_folio_items[] = $node;
        }
    }


    return theme('ironfolio_admin_list', array('categories' => $categories,
        'current_cat_id' => $current_cat_id,
        'iron_folio_items' => $iron_folio_items)
    );
}