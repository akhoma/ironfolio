<?php
global $base_path, $language_url;
$current_url_path = $base_path;
$current_url_path .=  $language_url->prefix ?  $language_url->prefix . '/' : '';
?>
<h1>language select</h1>
<ul>
    <li><a href="<?php echo $base_path . 'en/' . "admin/ironfolio/" . $current_cat_id ?>">English</a></li>
    <li><a href="<?php echo $base_path . 'ru/' . "admin/ironfolio/" . $current_cat_id ?>">Русский</a></li>
</ul>



<h1>Cats</h1>
<ul>
<?php foreach ($categories as $cat): ?>
    <?php
        $cat_class = "";
           if ($current_cat_id == $cat->tid) {
               $cat_class = 'active';
           }
    ?>
    <li class="<?php echo $cat_class; ?>">
        <a href="<?php echo $current_url_path . "admin/ironfolio/$cat->tid"; ?>"><?php echo $cat->name; ?></a>
    </li>
<?php endforeach; ?>
</ul>

<br />
<h1>Items</h1>
<?php foreach ($iron_folio_items as $item): ?>
    <li><?php echo $item->title; ?></li>
<?php endforeach; ?>

