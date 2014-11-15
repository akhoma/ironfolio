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

    // get language code
    global $language;
    $lang = $language->language;

    // get categories
    $vid = taxonomy_vocabulary_machine_name_load('folio_types ')->vid;
    $tax_tree = taxonomy_get_tree($vid);
    if (!$current_cat_id) {
        $current_cat_id = $tax_tree[0]->tid;
    }

    $categories = array();
    foreach ($tax_tree as $t_item) {
        $i18n_object = i18n_get_object('taxonomy_term', $t_item->tid);
        $translated_term = $i18n_object->localize($lang);
        $categories[] = $translated_term;
    }


    // get folio items by lang and cat
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node')
        ->propertyCondition('status', 1)
        ->propertyCondition('type', array('iron_folio'))
        ->fieldOrderBy('field_sort_order', 'value', 'DESC');
    $result = $query->execute();
    $nodesIds = array();
    foreach ($result['node'] as $n_item) {
        $nodesIds[] = (int) $n_item->nid;
    }
    $nodes = node_load_multiple($nodesIds, array('type' => 'iron_folio', 'language' => $lang));

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