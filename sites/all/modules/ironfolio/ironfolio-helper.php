<?php
class IronFolioHelper {
    public function renderFolioNodeFieldImage($item) {
        $view = field_view_field('node', $item, 'field_preview_image');
        return render($view);
    }

}