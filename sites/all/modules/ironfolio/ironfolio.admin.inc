<?php
/**
 * Created by JetBrains PhpStorm.
 * User: 2kish
 * Date: 12.11.14
 * Time: 22:12
 * To change this template use File | Settings | File Templates.
 */

require_once 'ironfolio-lib.php';
require_once 'ironfolio-helper.php';

function admin_ironfolio() {
    drupal_add_js('
jQuery(document).ready(function () {
	IronFolio.editForm.init();
  });', 'inline');
    return drupal_get_form('form_ironfolio_edit_form');
}

function form_ironfolio_edit_form($form, &$form_state) {
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

    $helper = new IronFolioHelper;
    $form['nodes_sort_order'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'node_sort_order',
        ),
    );
    $form['nodes_to_delete'] = array(
        '#type' => 'hidden',
        '#attributes' => array(
            'id' => 'nodes_to_delete',
        ),
    );

    $form['submit_button'] = array(
        '#type' => 'submit',
        '#value' => t('Сохранить данные'),
    );

    $form['some_text'] = array(
        '#markup' =>     theme('ironfolio_admin_list', array('categories' => $categories,
                'current_cat_id'   => $current_cat_id,
                'iron_folio_items' => $iron_folio_items,
                'helper'           => $helper)
        )
    );

    return $form;
}

function form_ironfolio_edit_form_validate($form, &$form_state) {

}

function form_ironfolio_edit_form_submit($form, &$form_state) {
    $nodesToSortIds = explode(',', $form['nodes_sort_order']['#value']);
    $ironFolioModel = new IronFolioModel;
    $ironFolioModel->changeSortOrder($nodesToSortIds);

    $nodesToDeleteIds = explode(',', $form['nodes_to_delete']['#value']);
    $ironFolioModel->deleteFolioItems($nodesToDeleteIds);

    drupal_set_message(t('Данные сохранины'), $type = 'status');

}