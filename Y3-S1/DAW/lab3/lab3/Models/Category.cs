﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace lab3.Models {
    public class Category {
        [Key]
        public int CategoryId { get; set; }
        [Required]
        public string CategoryName { get; set; }

        public virtual ICollection<Article> Article { get; set; }
    }
}