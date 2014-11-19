<?php
/**
 * Iron folio helper
 * @package 2kish
 * @subpackage 2kish_iron_folio
 */
class IronFolioHelper {
    public function renderFolioNodeFieldImage($item) {
        $view = field_view_field('node', $item, 'field_preview_image', array('type' => 'image', 'settings' => array('image_style' => 'medium')));
        return render($view);
    }

}