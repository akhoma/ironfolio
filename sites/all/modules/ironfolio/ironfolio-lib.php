<?php
class IronFolioModel {

    private $_folioNodeType = 'iron_folio',
            $_folioTaxonomyName = 'folio_types';

    public function getFolioItemsByCatAndLang($catId, $lang) {
        $query = new EntityFieldQuery();
        $query->entityCondition('entity_type', 'node')
            ->propertyCondition('status', 1)
            ->propertyCondition('type', array($this->_folioNodeType))
            ->fieldOrderBy('field_sort_order', 'value', 'DESC');
        $result = $query->execute();
        $nodesIds = array();
        foreach ($result['node'] as $n_item) {
            $nodesIds[] = (int) $n_item->nid;
        }
        $nodes = node_load_multiple($nodesIds, array('type' => $this->_folioNodeType, 'language' => $lang));

        $iron_folio_items = array();
        foreach ($nodes as $node) {
            if ($node->field_category['und'][0]['tid'] == $catId) {
                $iron_folio_items[] = $node;
            }
        }

        return $iron_folio_items;
    }

    public function getFolioCategories($lang) {
        $vid = taxonomy_vocabulary_machine_name_load($this->_folioTaxonomyName)->vid;
        $tax_tree = taxonomy_get_tree($vid);

        $categories = array();
        foreach ($tax_tree as $t_item) {
            $i18n_object = i18n_get_object('taxonomy_term', $t_item->tid);
            $translated_term = $i18n_object->localize($lang);
            $categories[] = $translated_term;
        }

        return $categories;
    }

}