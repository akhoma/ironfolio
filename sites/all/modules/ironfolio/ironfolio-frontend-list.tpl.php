<?php
global $base_path, $language_url, $base_url;
$current_url_path = $base_path;
$current_url_path .=  $language_url->prefix ?  $language_url->prefix . '/' : '';
?>
<div class="ironfolio-frontend">

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
                <a class="<?php echo $cat_class; ?>" href="<?php echo $current_url_path . "ironfolio/$cat->tid"; ?>"><?php echo $cat->name; ?></a>
            </li>
        <?php endforeach; ?>
        </ul>
    </div>

    <fieldset id="edit-filters" class="form-wrapper">
        <ul class="folioitems">
        <?php for($i = 0; $i < count($iron_folio_items); $i++): ?>
            <?php
                $item = $iron_folio_items[$i];
            ?>
            <li class="folio-item" folio-item-id="<?php echo $item->nid ?>">
                <?php
                    echo $helper->renderFolioNodeFieldImage($item);
                ?>
            </li>
        <?php endfor; ?>
        </ul>
    </fieldset>



    <ul id="folio-pager">
    <?php for($i = 1; $i<=$pager['pageCount']; $i++): ?>
        <li><a href="<?php echo $current_url_path . "ironfolio/$current_cat_id/?page=" . $i ?>">Page <?php echo $i; ?></a></li>
     <?php endfor; ?>
    </ul>
</div>