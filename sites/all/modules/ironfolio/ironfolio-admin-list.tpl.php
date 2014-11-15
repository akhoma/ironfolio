<?php
global $base_path, $language_url;
$current_url_path = $base_path;
$current_url_path .=  $language_url->prefix ?  $language_url->prefix . '/' : '';
$languages = language_list('enabled');
?>
<div class="ironfolio-admin">
    <fieldset id="edit-filters" class="form-wrapper">
        <legend><span class="fieldset-legend">Выбор языка</span></legend>
        <ul class="languages">
        <?php foreach($languages[1] as $lang_item): ?>
            <li><a class="<?php if ($lang_item->prefix == $language_url->prefix) echo 'active'; ?>"
                   href="<?php  echo $base_path . $lang_item->prefix . '/' . "admin/ironfolio/" . $current_cat_id ?>">
                    <?php echo $lang_item->native; ?>
                </a>
            </li>
        <?php endforeach; ?>
        </ul>
    </fieldset>

    <div id="edit-filters" class="admin-panel">
        <h3>Категории</h3>
        <ul class="categories">
        <?php foreach ($categories as $cat): ?>
            <?php
                $cat_class = "";
                   if ($current_cat_id == $cat->tid) {
                       $cat_class = 'active';
                   }
            ?>
            <li>
                <a class="<?php echo $cat_class; ?>" href="<?php echo $current_url_path . "admin/ironfolio/$cat->tid"; ?>"><?php echo $cat->name; ?></a>
            </li>
        <?php endforeach; ?>
        </ul>
    </div>

    <fieldset id="edit-filters" class="form-wrapper">
        <legend><span class="fieldset-legend">Портфолио</span></legend>
        <a class="button" href="<?php echo $current_url_path . "node/add/iron-folio/?destination=admin/ironfolio/$current_cat_id/"; ?>">Добавить работу</a>
        <ul class="folioitems">
        <?php for($i = 0; $i < count($iron_folio_items); $i++): ?>
            <?php
                $item = $iron_folio_items[$i];
                $prev_item = isset($iron_folio_items[$i-1]) ? $iron_folio_items[$i-1] : false;
                $next_item = isset($iron_folio_items[$i+1]) ? $iron_folio_items[$i+1] : false;
            ?>
            <li>
                <?php
                    echo $helper->renderFolioNodeFieldImage($item);
                ?>
                <?php // echo $item->field_sort_order['und'][0]['value']; ?>
                <div class="folio-item-navigation">
                    <?php if ($prev_item): ?>
                        <a class="folio-up" href="<?php echo $current_url_path . "admin/ironfolio/changesortorder/$item->nid/$prev_item->nid/"; ?>"></a>
                    <?php endif ?>

                    <?php if ($next_item): ?>
                        <a class="folio-down" href="<?php echo $current_url_path . "admin/ironfolio/changesortorder/$item->nid/$next_item->nid/"; ?>"></a>
                    <?php endif ?>

                    <a class="folio-edit" href="<?php echo $current_url_path . "node/$item->nid/edit/?destination=admin/ironfolio/$current_cat_id/"; ?>"></a>
                    <a class="folio-delete" href="<?php echo $current_url_path . "node/$item->nid/delete/?destination=admin/ironfolio/$current_cat_id/"; ?>"></a>
                </div>
            </li>
        <?php endfor; ?>
        </ul>
    </fieldset>
</div>